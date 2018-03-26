#include "Directional.h"

Directional::Directional()
	:Light(),
	ls(1.0),
	color(1.0),
	dir(0, 1, 0)
{

}

Directional::Directional(const Directional& dl)
	:Light(dl),
	ls(dl.ls),
	color(dl.color),
	dir(dl.dir)
{}

Directional& Directional::operator= (const Directional& rhs)
{
	if (this == &rhs)
		return (*this);

	Light::operator= (rhs);

	ls = rhs.ls;
	color = rhs.color;
	dir = rhs.dir;

	return (*this);
}

Directional::~Directional(){}

glm::vec3 Directional::get_direction(ShadeRec& sr) {
	return dir;
}

glm::vec3 Directional::L(ShadeRec& s)
{
	return ls * color;
}

// if ray.o can see the light
bool Directional::in_shadow(const Ray& ray, const ShadeRec& sr) const
{
	float t;
	int num_objects = sr.w.objects.size();

	for (int j = 0; j < num_objects; j++) {
		if (sr.w.objects[j]->shadow_hit(ray, t))
			return true;
	}
	return false;
}