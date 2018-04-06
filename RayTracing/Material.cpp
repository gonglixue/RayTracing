#include "Material.h"
#include "Constants.h"

Material::Material()
{
	shadows = true;
}

Material::Material(const Material& m)
	:shadows(m.shadows)
{

}

Material& Material::operator= (const Material& rhs)
{
	if (this == &rhs)
		return (*this);

	this->shadows = rhs.shadows;
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

void Material::set_shadows(bool isOpen)
{
	shadows = isOpen;
}

glm::vec3 Material::get_Le(ShadeRec& sr) const {
	return BLACK;
}

glm::vec3 Material::area_light_shade(ShadeRec& sr)
{
	return BLACK;
}

glm::vec3 Material::path_shade(ShadeRec& sr) {
	printf("nonsense path_shade in Material\n");
	return BLACK;
}

void Material::set_sampler(Sampler* sampler_ptr)
{

}

glm::vec3 Material::global_shade(ShadeRec& sr)
{
	return BLACK;
}