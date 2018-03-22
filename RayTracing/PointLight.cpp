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
	return (location - s.hit_point);
}

glm::vec3 PointLight::L(ShadeRec& sr)
{
	return ls * color;
}