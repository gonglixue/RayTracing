#ifndef __GEOMETRIC_OBJECT_H__
#define __GEOMETRIC_OBJECT_H__

#include <math.h>

#include "Constants.h"
#include "BBox.h"
#include "Ray.h"


//class Material;
class ShadeRec;

class GeometricObject
{
public:
	GeometricObject();
	GeometricObject(const GeometricObject& object);

	virtual ~GeometricObject();
	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
	glm::vec3 get_color() { return this->color; }
	void set_color(const glm::vec3& _color);
	void set_color(float x, float y, float z);

protected:
	glm::vec3 color;
	GeometricObject& operator= (const GeometricObject& rhs);
};

inline void GeometricObject::set_color(const glm::vec3& _color)
{
	color = _color;
}

inline void GeometricObject::set_color(float x, float y, float z)
{
	glm::vec3 new_color = glm::vec3(x, y, z);
	set_color(new_color);
}

#endif