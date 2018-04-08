#include "GlossyReflector.h"

GlossyReflector::GlossyReflector()
	:Phong(),
	glossy_specular_brdf(new GlossySpecular)
{}

GlossyReflector::~GlossyReflector(void) {
	if (glossy_specular_brdf) {
		delete glossy_specular_brdf;
		glossy_specular_brdf = NULL;
	}
}

glm::vec3 GlossyReflector::path_shade(ShadeRec& sr)
{
	glm::vec3 L(0);
	glm::vec3 wo = -sr.ray.d;
	glm::vec3 wi;
	float pdf;

	glm::vec3 fr = glossy_specular_brdf->sample_f(sr, wo, wi, pdf);
	Ray reflected_ray(sr.hit_point, wi);

	L = fr * glm::dot(sr.normal, wi) / pdf * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1);
	return L;
}