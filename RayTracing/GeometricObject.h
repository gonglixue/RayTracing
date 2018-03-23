#ifndef __GEOMETRIC_OBJECT_H__
#define __GEOMETRIC_OBJECT_H__

#include <math.h>

#include "Constants.h"
#include "BBox.h"
#include "Ray.h"


class Material;
class ShadeRec;

class GeometricObject
{
public:
	GeometricObject();
	GeometricObject(const GeometricObject& object);
	virtual ~GeometricObject();

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

	glm::vec3 get_color() { return this->color; }
	Material* get_material() const;
	virtual BBox get_bounding_box();

	void set_color(const glm::vec3& _color);
	void set_color(float x, float y, float z);
	virtual void set_material(Material* m_ptr);
	virtual void set_bounding_box();
	
	// 只对发光体有效
	virtual glm::vec3 sample();
	virtual float pdf(const ShadeRec& sr);

	// The following two functions allow us to simplify the code for smooth shaded triangle meshes
	virtual glm::vec3 get_normal() const;
	virtual glm::vec3 get_normal(const glm::vec3& p);

	int object_id;					// used for collision debug
protected:
	glm::vec3 color;				// 只在简单版里用到
	mutable Material* material_ptr; // mutable allows the const functions Compound::hit, Instance::hit, and RegularGrid::hit to assign to material_ptr
	
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