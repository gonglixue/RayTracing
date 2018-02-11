#include "GeometricObject.h"

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

