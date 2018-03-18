#include "Constants.h"
#include "BRDF.h"

BRDF::BRDF()
	:sampler_ptr(NULL)
{

}

BRDF::BRDF(const BRDF& brdf)
{
	sampler_ptr = brdf.sampler_ptr;
}

BRDF& BRDF::operator= (const BRDF& rhs)
{
	if (this == &rhs)
		return (*this);

	if (sampler_ptr) {
		// delete sampler_ptr;
		//sampler_ptr = NULL;
	}
	if (rhs.sampler_ptr)
		sampler_ptr = rhs.sampler_ptr;

	return (*this);
}

BRDF::~BRDF()
{
	if (sampler_ptr)
	{
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
}

void BRDF::set_sampler(Sampler* s_ptr)
{
	sampler_ptr = s_ptr;
	sampler_ptr->map_samples_to_hemisphere(1);
}

glm::vec3 BRDF::f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const
{
	return BLACK;
}

glm::vec3 BRDF::sample_f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const
{
	return BLACK;
}

glm::vec3 BRDF::sample_f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi, float& pdf) const
{
	return BLACK;
}

glm::vec3 BRDF::rho(const ShadeRec& sr, const glm::vec3& wo) const
{
	return BLACK;
}