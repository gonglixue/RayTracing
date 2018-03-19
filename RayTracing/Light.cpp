#include "Light.h"
#include "Constants.h"

Light::Light()
{

}

Light::Light(const Light& ls)
{

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