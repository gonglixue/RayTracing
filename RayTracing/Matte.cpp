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

glm::vec3 Matte::shade(ShadeRec& sr)
{
	glm::vec3 wo = -sr.ray.d;
	//glm::vec3 L = ambient_brdf->rho(sr, wo) *
		//sr.w.ambient_ptr->L(sr);		// 材质ambient颜色 * 环境光颜色
	glm::vec3 L = glm::vec3(0, 0, 0);
	//printf("ambient color:(%f, %f, %f)\n", L.x, L.y, L.z);
	const std::vector<Light*>& lights = sr.w.lights;
	int num_lights = lights.size();

	for (int j = 0; j < num_lights; j++)
	{
		glm::vec3 wi = lights[j]->get_direction(sr);
		float ndotwi = glm::dot(sr.normal, wi);

		if (ndotwi > kEpsilon)	//该点对光源可见
			L = L + (ndotwi * diffuse_brdf->f(sr, wo, wi) * lights[j]->L(sr));		// cos * (材质颜色 * 光源颜色）
		else
			printf("[%d]: %f %f %f光源不可见\n", sr.hit_object_id, sr.hit_point.x, sr.hit_point.y, sr.hit_point.z);
		if (ndotwi > 1.0) {
			printf("Error: ndotwi=%f\n", ndotwi);
			exit(1);
		}
	}
	//return glm::vec3(1, 0, 0);
	return L;
}