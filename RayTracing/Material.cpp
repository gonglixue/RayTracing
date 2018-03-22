#include "Material.h"
#include "Constants.h"

Material::Material()
{

}

Material::Material(const Material& m)
{

}

Material& Material::operator= (const Material& rhs)
{
	if (this == &rhs)
		return (*this);

	return (*this);
}

Material::~Material()
{

}

// 与光照发生作用，以计算相应的反射辐射度
glm::vec3 Material::shade(ShadeRec& sr)
{
	return BLACK;
}