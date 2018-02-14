#include "Jittered.h"

Jittered::Jittered()
	:Sampler()
{
	generate_samples();
}

Jittered::Jittered(const int _num_samples)
	: Sampler(_num_samples)
{
	generate_samples();
}

Jittered::Jittered(const int _num_samples, const int _num_sets)
	: Sampler(_num_samples, _num_samples)
{
	generate_samples();
}

Jittered::Jittered(const Jittered& jitterd)
	: Sampler(jitterd)
{
	generate_samples();
}

Jittered& Jittered::operator= (const Jittered& rhs)
{
	if (this == &rhs)
		return (*this);

	Sampler::operator= (rhs);

	return (*this);
}

Jittered::~Jittered()
{}

// 在单位正方形内生成num_samples * num_sets个采样点
void Jittered::generate_samples()
{
	int n = (int)sqrt(num_samples);

	for (int p = 0; p < num_sets; p++) {
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++) {
				glm::dvec2 sp((k + rand_float()) / n, (j + rand_float()) / n);
				samples.push_back(sp);
			}
		}
	}
}