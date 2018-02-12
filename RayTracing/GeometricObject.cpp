#include "GeometricObject.h"
#include "ShadeRec.h"

GeometricObject::GeometricObject():color(BLACK)
{}

GeometricObject::GeometricObject(const GeometricObject& object)
	: color(object.color)
{
	// TODO
	// material
}

GeometricObject& GeometricObject::operator= (const GeometricObject& rhs)
{
	if (this == &rhs)
		return *this;
	color = rhs.color;
	// TODO 
	// material

	return *this;
}

GeometricObject::~GeometricObject()
{}

bool GeometricObject::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
{
	return false;
}

