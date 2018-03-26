#include "PointLight.h"
#include "ShadeRec.h"
PointLight::PointLight()
	:Light(),
	ls(1.0),
	color(1.0),
	location(200, 200, 200)
{

}

PointLight::PointLight(const PointLight& plight)
	:Light(plight),
	ls(plight.ls),
	color(plight.color),
	location(plight.location)
{

}

PointLight& PointLight::operator= (const PointLight& rhs)
{
	if (this == &rhs)
		return (*this);

	PointLight::operator= (rhs);

	ls = rhs.ls;
	color = rhs.color;
	location = rhs.location;

	return (*this);


}

PointLight::~PointLight() {

}

glm::vec3 PointLight::get_direction(ShadeRec& s)
{
	glm::vec3 light_dir = location - s.hit_point;
	light_dir = glm::normalize(light_dir);
	return light_dir;
}

glm::vec3 PointLight::L(ShadeRec& sr)
{
	return ls * color;
}

bool PointLight::in_shadow(const Ray& ray, const ShadeRec& sr) const
{
	float t;
	int num_object = sr.w.objects.size();
	float d = glm::distance(glm::vec3(ray.o), this->location);

	for (int j = 0; j < num_object; j++) {
		if (sr.w.objects[j]->shadow_hit(ray, t) && t < d)
			return true;
	}

	return false;
	
}