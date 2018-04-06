#include "PerfectSpecular.h"

PerfectSpecular::PerfectSpecular()
	:BRDF(),
	kr(0.0),
	color(1.0)
{

}

PerfectSpecular::~PerfectSpecular()
{}

glm::vec3 PerfectSpecular::f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const
{
	printf("nonsense f in PerfectSpecular\n");
	exit(1);
	return BLACK;
}


// wi: 视线方向的反射方向
// 在Relective::shade中调用
glm::vec3 PerfectSpecular::sample_f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi) const
{
	float ndotwo = glm::dot(sr.normal, wo);

	wi = -wo + 2.0f * ndotwo * sr.normal;

	return kr / fabs(glm::dot(sr.normal, wi)) * color;
}

// used in path tracing
glm::vec3 PerfectSpecular::sample_f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi, float& pdf) const
{
	float ndotwo = glm::dot(sr.normal, wo);
	wi = -wo + 2.0f * ndotwo * sr.normal;
	pdf = fabs(glm::dot(sr.normal, wi));

	return kr * color;
}

glm::vec3 PerfectSpecular::rho(const ShadeRec& sr, const glm::vec3& wo) const
{
	return BLACK;
}