#include "Matte.h"
#include "Constants.h"
Matte::Matte()
	:Material(),
	ambient_brdf(new Lambertian),
	diffuse_brdf(new Lambertian)
{

}

Matte::Matte(const Matte& m)
	:Material(m)
{
	if (m.ambient_brdf) {
		ambient_brdf = new Lambertian(*(m.ambient_brdf));
	}
	else
		ambient_brdf = NULL;

	if (m.diffuse_brdf) {
		diffuse_brdf = new Lambertian(*(m.diffuse_brdf));
	}
	else
		diffuse_brdf = NULL;
}

Matte&
Matte::operator=(const Matte& rhs)
{
	if (this == &rhs)
		return (*this);

	Material::operator=(rhs);

	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}
	if (rhs.ambient_brdf)
		ambient_brdf = new Lambertian(*(rhs.ambient_brdf));

	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}

	if (rhs.diffuse_brdf)
		diffuse_brdf = new Lambertian(*(rhs.diffuse_brdf));

	return (*this);
}

Matte::~Matte(void) {

	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}

	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}
}

void Matte::set_sampler(Sampler* sampler_ptr)
{
	diffuse_brdf->set_sampler(sampler_ptr);
}

glm::vec3 Matte::shade(ShadeRec& sr)
{
	glm::vec3 wo = -sr.ray.d;
	glm::vec3 L = ambient_brdf->rho(sr, wo) *
		sr.w.ambient_ptr->L(sr);		// 材质ambient颜色 * 环境光颜色
	//glm::vec3 L = glm::vec3(0, 0, 0);
	//printf("ambient color:(%f, %f, %f)\n", L.x, L.y, L.z);
	const std::vector<Light*>& lights = sr.w.lights;
	int num_lights = lights.size();

	for (int j = 0; j < num_lights; j++)
	{
		glm::vec3 wi = lights[j]->get_direction(sr);
		float ndotwi = glm::dot(sr.normal, wi);

		if (ndotwi > 0.0) {	//该点对光源可见
			bool in_shadows = false;
			if (sr.w.lights[j]->casts_shadows()) {
				Ray shadowRay(sr.hit_point, wi);
				in_shadows = sr.w.lights[j]->in_shadow(shadowRay, sr);
			}

			if (!in_shadows)
				L = L + (ndotwi * diffuse_brdf->f(sr, wo, wi) * lights[j]->L(sr));		// cos * (材质颜色 * 光源颜色）
			else // test
			{
				//printf("in shadow \n");
				//return glm::vec3(255, 0, 0);
			}
		}
		//else
			//printf("[%d]: %f %f %f光源不可见\n", sr.hit_object_id, sr.hit_point.x, sr.hit_point.y, sr.hit_point.z);

	}
	//return glm::vec3(1, 0, 0);
	return L;
}

glm::vec3 Matte::area_light_shade(ShadeRec& sr)
{
	glm::vec3 wo = -sr.ray.d;
	glm::vec3 L = ambient_brdf->rho(sr, wo) *
		sr.w.ambient_ptr->L(sr);

	int num_lights = sr.w.lights.size();
	for (int j = 0; j < num_lights; j++) {
		glm::vec3 wi = sr.w.lights[j]->get_direction(sr);
		float ndotwi = glm::dot(sr.normal, wi);

		if (ndotwi > 0.0) {
			bool in_shadow = false;
			if (sr.w.lights[j]->casts_shadows()) {
				Ray shadow_ray(sr.hit_point, wi);
				in_shadow = sr.w.lights[j]->in_shadow(shadow_ray, sr);
			}
			if (!in_shadow)
				L = L + (ndotwi / sr.w.lights[j]->pdf(sr))*(diffuse_brdf->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * sr.w.lights[j]->G(sr));
		}
	}

	return L;
}

glm::vec3 Matte::path_shade(ShadeRec& sr)
{
	glm::vec3 wo = -sr.ray.d;
	glm::vec3 wi;	// 上半球采样得到的反射光线，用于后续path trace
	float pdf;
	glm::vec3 f = diffuse_brdf->sample_f(sr, wo, wi, pdf);
	float ndotwi = glm::dot(sr.normal, wi);
	Ray reflected_ray(sr.hit_point, wi);

	return (ndotwi / pdf) * f * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) ;
}

glm::vec3 Matte::global_shade(ShadeRec& sr)
{
	glm::vec3 L;
	if (sr.depth == 0)
		L = area_light_shade(sr);

	glm::vec3 wi;
	glm::vec3 wo = -sr.ray.d;
	float pdf;
	glm::vec3 f = diffuse_brdf->sample_f(sr, wo, wi, pdf);
	float ndotwi = glm::dot(sr.normal, wi);
	Ray reflected_ray(sr.hit_point, wi);

	L = L + (ndotwi / pdf) * f * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1);
	return L;
}