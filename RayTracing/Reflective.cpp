#include "Reflective.h"
#include <iostream>

Reflective::Reflective()
	:Phong(),
	reflective_brdf(new PerfectSpecular)
{

}

Reflective::~Reflective()
{}

glm::vec3 Reflective::shade(ShadeRec& sr)
{
	// 直接光照
	glm::vec3 L = Phong::shade(sr);		// 基类
	glm::vec3 wo = -sr.ray.d;
	glm::vec3 wi;

	glm::vec3 fr = reflective_brdf->sample_f(sr, wo, wi);

	// 以碰撞点为起点，wi为方向的光线
	Ray reflected_ray(sr.hit_point, wi);



	L = L + glm::dot(sr.normal, wi) * (fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1));

	return L;
}

glm::vec3 Reflective::area_light_shade(ShadeRec& sr)
{
	// 
	printf("Reflective::area_light not implemented\n");
	exit(1);
	return BLACK;
}

glm::vec3 Reflective::path_shade(ShadeRec& sr)
{
	glm::vec3 wo = -sr.ray.d;
	glm::vec3 wi;
	float pdf;

	glm::vec3 fr = reflective_brdf->sample_f(sr, wo, wi, pdf);
	Ray reflected_ray(sr.hit_point, wi);

	if (glm::dot(sr.normal, wo) < 0) {
		//printf("%s:", mat_name.c_str());
		std::cout<< mat_name;
		printf(" need reverse\n");
	}
	
	return glm::dot(sr.normal, wi) / pdf
		* (fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1));
}

glm::vec3 Reflective::global_shade(ShadeRec& sr)
{
	glm::vec3 wo = -sr.ray.d;
	glm::vec3 wi;
	float pdf;

	glm::vec3 fr = reflective_brdf->sample_f(sr, wo, wi, pdf);
	Ray reflected_ray(sr.hit_point, wi);

	if(sr.depth == 0)
		return glm::dot(sr.normal, wi) / pdf
		* (fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 2));

	else
		return glm::dot(sr.normal, wi) / pdf
		* (fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1));
}
