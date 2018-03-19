#include "Ambient.h"

Ambient::Ambient()
	:Light(),
	ls(1.0),
	color(1.0)
{

}

Ambient::Ambient(const Ambient& ambient)
	:Light(ambient),
	ls(ambient.ls),
	color(ambient.color)
{

}

Ambient& Ambient::operator= (const Ambient& rhs)
{
	if (this == &rhs)
		return (*this);

	Light::operator= (rhs);

	ls = rhs.ls;
	color = rhs.color;

	return (*this);
}

Ambient::~Ambient()
{

}

glm::vec3 Ambient::get_direction(ShadeRec& s)
{
	return glm::vec3(0, 0, 0);
}

glm::vec3 Ambient::L(ShadeRec& sr)
{
	return ls*color;
}