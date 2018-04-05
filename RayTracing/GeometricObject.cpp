#include "GeometricObject.h"
#include "ShadeRec.h"
#include "Material.h"
#include "Sampler.h"

GeometricObject::GeometricObject():color(BLACK),shadows(true)
{}

GeometricObject::GeometricObject(const GeometricObject& object)
	: color(object.color)
{
	if (object.material_ptr)
		material_ptr = new Material(*(object.material_ptr));
}

GeometricObject& GeometricObject::operator= (const GeometricObject& rhs)
{
	if (this == &rhs)
		return *this;

	color = rhs.color;
	
	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}

	if (rhs.material_ptr) {
		material_ptr = new Material(*(rhs.material_ptr));
	}

	return *this;
}

GeometricObject::~GeometricObject()
{}

bool GeometricObject::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
{
	return false;
}

void GeometricObject::set_material(Material* m_ptr)
{
	material_ptr = m_ptr;
}

Material* GeometricObject::get_material() const {
	return material_ptr;
}

void GeometricObject::set_bounding_box()
{

}

BBox GeometricObject::get_bounding_box()
{
	return BBox();
}

glm::vec3 
GeometricObject::sample(void) {
	return (glm::vec3(0.0));
}


// ----------------------------------------------------------------------- pdf
// returns the probability density function for area light shading

float
GeometricObject::pdf(const ShadeRec& sr) {
	return (0.0);
}

glm::vec3
GeometricObject::get_normal(void) const {
	return (glm::vec3(0));
}

glm::vec3 GeometricObject::get_normal(const glm::vec3& p) {
	return glm::vec3(0);
}

bool GeometricObject::shadow_hit(const Ray& ray, float& t)const
{
	return false;
}


void GeometricObject::add_object(GeometricObject* object_ptr)
{

}

void GeometricObject::set_sampler(Sampler* sampler)
{

}
