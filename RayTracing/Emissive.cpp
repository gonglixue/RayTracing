#include "Emissive.h"

Emissive::Emissive():
	Material(),
	ls(1.0),
	color(1.0)
{}

Emissive::Emissive(const Emissive& e):
	Material(e),
	ls(e.ls),
	color(e.color)
{}

Emissive& Emissive::operator= (const Emissive& rhs)
{
	if (this == &rhs)
		return (*this);

	Material::operator=(rhs);
	ls = rhs.ls;
	color = rhs.color;
	return (*this);
}

Emissive::~Emissive() {

}

// 当入射方向与对象表面法线位于同一侧时，返回颜色
glm::vec3 Emissive::area_light_shade(ShadeRec& sr)
{
	if (glm::dot(-sr.normal, glm::vec3(sr.ray.d)) > 0.0)
		return ls * color;
	else
		return BLACK;
}

glm::vec3 Emissive::shade(ShadeRec& sr)
{
	if (glm::dot(-sr.normal, glm::vec3(sr.ray.d)) > 0.0)
		return ls * color;
	else
		return BLACK;
}

glm::vec3 Emissive::get_Le(ShadeRec& sr) const
{
	return ls * color;
}

glm::vec3 Emissive::path_shade(ShadeRec& sr)
{
	if(sr.depth > 1)
		printf("Emissive path_shade\n");
	return ls * color;
}

glm::vec3 Emissive::global_shade(ShadeRec& sr)
{
	if (sr.depth == 1)
		return BLACK;
	if (glm::dot(-sr.normal, glm::vec3(sr.ray.d)) > 0.0)
		return ls * color;
	else
		return BLACK;
}