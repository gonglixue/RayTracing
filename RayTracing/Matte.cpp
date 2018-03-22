#include "Matte.h"

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

glm::vec3 Matte::shade(ShadeRec& sr)
{
	glm::vec3 wo = -sr.ray.d;
	glm::vec3 L = ambient_brdf->rho(sr, wo) *
		sr.w.ambient_ptr->L(sr);

	const std::vector<Light*>& lights = sr.w.lights;
	int num_lights = lights.size();

	for (int j = 0; j < num_lights; j++)
	{
		glm::vec3 wi = lights[j]->get_direction(sr);
		float ndotwi = glm::dot(sr.normal, wi);

		if (ndotwi > 0.0)	//该店对光源可见
			L += ndotwi * diffuse_brdf->f(sr, wo, wi) * lights[j]->L(sr);		// cos * (材质颜色 * 光源颜色）
	}

	return L;
}