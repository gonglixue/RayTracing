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

// ����շ������ã��Լ�����Ӧ�ķ�������
glm::vec3 Material::shade(ShadeRec& sr)
{
	return BLACK;
}