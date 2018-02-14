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