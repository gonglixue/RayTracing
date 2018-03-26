#include "Phong.h"


Phong::Phong()
	:Material(),
	ambient_brdf(new Lambertian),
	diffuse_brdf(new Lambertian),
	specular_brdf(new GlossySpecular)
{

}

Phong::Phong(const Phong& phong_mat)
	: Material(phong_mat)
{
	if (phong_mat.ambient_brdf)
		ambient_brdf = new Lambertian(*phong_mat.ambient_brdf);
	else
		ambient_brdf = NULL;

	if (phong_mat.diffuse_brdf)
		diffuse_brdf = new Lambertian(*phong_mat.diffuse_brdf);
	else
		diffuse_brdf = NULL;

	if (phong_mat.specular_brdf) {
		specular_brdf = new GlossySpecular(*(phong_mat.specular_brdf));
	}
	else
		specular_brdf = NULL;
}

Phong& Phong::operator= (const Phong& rhs)
{
	if (this == &rhs)
		return (*this);

	Material::operator=(rhs);

	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}
	if (rhs.ambient_brdf)
		this->ambient_brdf = new Lambertian(*(rhs.ambient_brdf));

	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}
	if (rhs.diffuse_brdf)
		this->diffuse_brdf = new Lambertian(*(rhs.diffuse_brdf));

	if (specular_brdf) {
		delete specular_brdf;
		specular_brdf = NULL;
	}
	if (rhs.specular_brdf)
		this->specular_brdf = new GlossySpecular(*(rhs.specular_brdf));

	return (*this);
}

Phong::~Phong()
{
	if (ambient_brdf)
		delete ambient_brdf;
	if (diffuse_brdf)
		delete diffuse_brdf;
	if (specular_brdf)
		delete specular_brdf;

	ambient_brdf = NULL;
	diffuse_brdf = NULL;
	specular_brdf = NULL;
}

glm::vec3 Phong::shade(ShadeRec& sr)
{
	glm::vec3 wo = -1.0 * sr.ray.d;
	glm::vec3 L = ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);

	int num_lights = sr.w.lights.size();
	for (int j = 0; j < num_lights; j++) {
		glm::vec3 wi = sr.w.lights[j]->get_direction(sr);
		float ndotwi = glm::dot(sr.normal, wi);

		if (ndotwi > 0.0) {
			bool in_shadow = false;
			if (sr.w.lights[j]->casts_shadows()) {
				Ray shadowRay(sr.hit_point, wi);
				in_shadow = sr.w.lights[j]->in_shadow(shadowRay, sr);
			}

			if (!in_shadow) {
				glm::vec3 temp = diffuse_brdf->f(sr, wo, wi) + specular_brdf->f(sr, wo, wi);
				L += ndotwi * temp * (sr.w.lights[j]->L(sr));
			}
		}
	}

	return L;
}