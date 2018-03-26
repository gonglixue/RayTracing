#include "Light.h"
#include "Constants.h"
#include <stdio.h>

Light::Light()
{
	shadows = true;
}

Light::Light(const Light& ls)
{
	shadows = ls.shadows;
}

Light& Light::operator= (const Light& rhs)
{
	if (this == &rhs)
		return (*this);

	return (*this);
}

Light::~Light()
{

}

glm::vec3 Light::L(ShadeRec& s)
{
	return BLACK;
}

bool Light::in_shadow(const Ray& ray, const ShadeRec& sr) const
{
	printf("Base Light in_shadow\n");
	return false;
}