#include "Lambertian.h"
#include "Constants.h"

Lambertian::Lambertian()
	:BRDF(),
	kd(0.0),
	cd(0.0)
{

}

Lambertian::Lambertian(const Lambertian& lamb)
	:BRDF(lamb),
	kd(lamb.kd),
	cd(lamb.cd)
{

}

Lambertian&
Lambertian::operator= (const Lambertian& rhs)
{
	if (this == &rhs)
		return (*this);

	BRDF::operator= (rhs);

	kd = rhs.kd;
	cd = rhs.cd;

	return (*this);
}

Lambertian::~Lambertian(){}

// Lambertian 与入射光线无关
glm::vec3 Lambertian::f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi) const
{
	float temp = invPI * this->kd;
	return temp * cd;
}

glm::vec3 Lambertian::sample_f(const ShadeRec& sr, const glm::vec3 &wo, glm::vec3& wi, float& pdf) const
{
	glm::vec3 w = sr.normal;
	glm::vec3 v = glm::cross(glm::vec3(0.0034, 1, 0.0071), w);
	v = glm::normalize(v);
	glm::vec3 u = glm::cross(v, w);

	glm::vec3 sp = sampler_ptr->sample_hemisphere();
	wi = sp.x * u + sp.y * v + sp.z * w;
	wi = glm::normalize(wi);	// wi是上半球采样得到的反射光线

	pdf = invPI * glm::dot(sr.normal, wi);

	return (float)(invPI * kd) * cd;
}

// 系数 * 光源颜色
glm::vec3 Lambertian::rho(const ShadeRec& sr, const glm::vec3& wo) const
{
	return (kd * cd);
}