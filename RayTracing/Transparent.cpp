#include "Transparent.h"

Transparent::Transparent()
	:Phong(),
	reflective_brdf(new PerfectSpecular),
	specular_btdf(new PerfectTransmitter)
{}

Transparent::~Transparent()
{
	if (reflective_brdf) {
		delete reflective_brdf;
		reflective_brdf = NULL;
	}
	if (specular_btdf) {
		delete specular_btdf;
		specular_btdf = NULL;
	}
}

glm::vec3 Transparent::shade(ShadeRec& sr)
{
	glm::vec3 L = Phong::shade(sr);	// direct illumination
	glm::vec3 wo = -sr.ray.d;
	glm::vec3 wi;
	// use sample_f to calculate wi
	glm::vec3 fr = reflective_brdf->sample_f(sr, wo, wi);

	Ray reflected_ray = Ray(sr.hit_point, wi);
	if (specular_btdf->tir(sr)) {
		L = L + sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1);
	}
	else {
		glm::vec3 wt;
		glm::vec3 ft = specular_btdf->sample_f(sr, wo, wt);
		Ray transmitted_ray(sr.hit_point, wt);	//折射光线

		L = L + fabs(glm::dot(sr.normal, wi)) * fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1);

		L = L + fabs(glm::dot(sr.normal, wt)) * ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, sr.depth + 1);
	}

	return L;
}

glm::vec3 Transparent::path_shade(ShadeRec& sr)
{
	// glm::vec3 L = Phong::shade(sr);	// direct illumination
	glm::vec3 L(0);
	glm::vec3 wo = -sr.ray.d;
	glm::vec3 wi;

	float pdf_r, pdf_t;
	// use sample_f to calculate wi
	glm::vec3 fr = reflective_brdf->sample_f(sr, wo, wi, pdf_r);

	Ray reflected_ray = Ray(sr.hit_point, wi);
	if (specular_btdf->tir(sr)) {
		// L = L + sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1);
		//?
		L = glm::dot(sr.normal, wi) / pdf_r
			* (fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1));
	}
	else {
		glm::vec3 wt;
		glm::vec3 ft = specular_btdf->sample_f(sr, wo, wt, pdf_t);
		Ray transmitted_ray(sr.hit_point, wt);	//折射光线

		L = L + fabs(glm::dot(sr.normal, wi))/pdf_r * fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1);

		L = L + fabs(glm::dot(sr.normal, wt))/pdf_t * ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, sr.depth + 1);
	}

	return L;
}