#include "Sampler.h"
#include <algorithm>

Sampler::Sampler()
	:num_samples(1),
	num_sets(83),
	count(0),
	jump(0) 
{
	// samples.reserve(num_samples * num_sets);
	setup_shuffled_indices();
}

Sampler::Sampler(const int ns)
	:num_samples(ns),
	num_sets(83),
	count(0),
	jump(0)
{
	// samples.reserve(num_samples * num_sets);
	setup_shuffled_indices();
}

Sampler::Sampler(const int ns, const int n_sets)
	:num_samples(ns),
	num_sets(n_sets),
	count(0),
	jump(0)
{
	// samples.reserve(num_samples * num_sets);
	setup_shuffled_indices();
}

Sampler::Sampler(const Sampler& s)
	:num_samples(s.num_samples),
	num_sets(s.num_sets),
	samples(s.samples),
	shuffled_indices(s.shuffled_indices),
	count(s.count),
	jump(s.jump)
{}

Sampler& Sampler::operator= (const Sampler& rhs)
{
	if (this == &rhs)
		return (*this);

	num_samples = rhs.num_samples;
	num_sets = rhs.num_sets;
	samples = rhs.samples;
	shuffled_indices = rhs.shuffled_indices;
	count = rhs.count;
	jump = rhs.jump;

	return (*this);
}

Sampler::~Sampler()
{}

void Sampler::set_num_sets(const int ns)
{
	num_sets = ns;
}

int Sampler::get_num_samples()
{
	return num_samples;
}

void Sampler::shuffle_x_coordinates()
{
	for (int p = 0; p < num_sets; p++) {
		for (int i = 0; i < num_samples - 1; i++)
		{
			int target = rand_int() % num_samples + p*num_samples;// target是在第p个set中的随机的一个点
			float temp = samples[i + p*num_samples + 1].x;			// 为什么要加1？
			samples[i + p*num_samples + 1].x = samples[target].x;
			samples[target].x = temp;
		}
	}
}

void Sampler::shuffle_y_coordinates()
{
	for (int p = 0; p < num_sets; p++) {
		for (int i = 0; i < num_samples - 1; i++)
		{
			int target = rand_int() % num_samples + p*num_samples;
			float temp = samples[i + p*num_samples + 1].y;
			samples[i + p*num_samples + 1].y = samples[target].y;
			samples[target].y = temp;
		}
	}
}


// shuffled_indices在某个set里是乱序的，但是总体的set是有序的
void Sampler::setup_shuffled_indices()
{
	shuffled_indices.reserve(num_samples * num_sets); // ?
	std::vector<int> indices;

	for (int j = 0; j < num_samples; j++)
		indices.push_back(j);		// 单个set的indices

	for (int p = 0; p < num_sets; p++) 
	{
		std::random_shuffle(indices.begin(), indices.end());

		for (int j = 0; j < num_samples; j++)
			shuffled_indices.push_back(indices[j]);		// 

	}
}

void Sampler::map_samples_to_unit_disk()
{
	int size = samples.size();
	float r, phi;		// polar coordinates
	glm::dvec2 sp;		// sample point on unit disk

	disk_samples.reserve(size);

	for (int j = 0; j < size; j++) {
		// map from [0,1] to [-1,1]
		sp.x = 2.0 * samples[j].x - 1.0f;
		sp.y = 2.0 * samples[j].y - 1.0f;

		if (sp.x > -sp.y) {
			if (sp.x > sp.y) {
				r = sp.x;
				phi = sp.y / sp.x;
			}
			else {
				r = sp.y;
				phi = 2 - sp.x / sp.y;
			}
		}
		else {
			if (sp.x < sp.y) {
				r = -sp.x;
				phi = 4 + sp.y / sp.x;
			}
			else {
				r = -sp.y;
				if (sp.y != 0.0)
					phi = 6 - sp.x / sp.y;
				else
					phi = 0.0;
			}
		}

		phi = phi * PI / 4.0;

		disk_samples[j].x = r * cos(phi);
		disk_samples[j].y = r * sin(phi);
	}

	samples.erase(samples.begin(), samples.end());
}

void Sampler::map_samples_to_hemisphere(const float e)
{
	int size = samples.size();
	hemisphere_samples.reserve(size);

	for (int j = 0; j < size; j++)
	{
		float cos_phi = cos(2 * PI*samples[j].x);
		float sin_phi = sin(2 * PI*samples[j].x);
		float cos_theta = pow(1 - samples[j].y, 1.0 / (e + 1.0));
		float sin_theta = sqrt(1.0 - cos_theta*cos_theta);

		float pu = sin_theta * cos_phi;
		float pv = sin_theta * sin_phi;
		float pw = cos_theta;

		hemisphere_samples.push_back(glm::dvec3(pu, pv, pw));
	}
	
}

/*	每个像素均采用同一采样点集的话，仍会产生失真
	因此引入jump，采样完num_samples个点后，从其他的set里采样
*/
glm::dvec2 Sampler::sample_unit_square()
{
	if (count % num_samples == 0)
		jump = (rand_int() % num_sets) * num_samples;

	// return (samples[jump + (count++ % num_samples)]);
	return samples[jump + shuffled_indices[jump + (count++ % num_samples)]];
}

glm::dvec2 Sampler::sample_unit_disk()
{
	if (count % num_samples == 0)
		jump = (rand_int() % num_sets) * num_samples;

	return disk_samples[jump + shuffled_indices[jump + (count++%num_samples)]];
}

glm::dvec3 Sampler::sample_hemisphere()
{
	if (count % num_samples == 0)  									// start of a new pixel
		jump = (rand_int() % num_sets) * num_samples;

	return (hemisphere_samples[jump + shuffled_indices[jump + count++ % num_samples]]);
	
}

