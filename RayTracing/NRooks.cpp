#include "NRooks.h"

NRooks::NRooks()
	:Sampler()
{
	generate_samples();
}

NRooks::NRooks(const int _num_samples)
	: Sampler(_num_samples)
{
	generate_samples();
}

NRooks::NRooks(const int _num_samples, const int _num_sets)
	: Sampler(_num_samples, _num_sets)
{
	generate_samples();
}

NRooks::NRooks(const NRooks& nrooks)
	:Sampler(nrooks)
{
	generate_samples();		// 拷贝构造函数要重新generate_samples()吗？
}

NRooks& NRooks::operator= (const NRooks& rhs)
{
	if (this == &rhs)
		return (*this);

	Sampler::operator=(rhs);

	return (*this);
}

NRooks::~NRooks()
{
}

void NRooks::generate_samples()
{
	for (int p = 0; p < num_sets; p++)
	{
		for (int j = 0; j < num_samples; j++)
		{
			glm::dvec2 pv;
			pv.x = (j + rand_float()) / num_samples;
			pv.y = (j + rand_float()) / num_samples;
			samples.push_back(pv);
		}
	}

	shuffle_x_coordinates();
	shuffle_y_coordinates();
}

