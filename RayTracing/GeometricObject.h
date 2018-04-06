#ifndef __GEOMETRIC_OBJECT_H__
#define __GEOMETRIC_OBJECT_H__

#include <math.h>

#include "Constants.h"
#include "BBox.h"
#include "Ray.h"


class Material;
class ShadeRec;
class Sampler;

class GeometricObject
{
public:
	GeometricObject();
	GeometricObject(const GeometricObject& object);
	virtual ~GeometricObject();

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
	virtual bool shadow_hit(const Ray& ray, float& t) const;	// 是否遮挡了ray
	void set_shadows(bool isOpen);

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

	// for combined object
	virtual void add_object(GeometricObject* object_ptr);
	
	virtual void set_sampler(Sampler* sampler);

	int object_id;					// used for collision debug
protected:
	glm::vec3 color;				// 只在简单版里用到
	mutable Material* material_ptr; // mutable allows the const functions Compound::hit, Instance::hit, and RegularGrid::hit to assign to material_ptr
	bool shadows;					// 该物体上是否可被投影阴影(x) 是否会成为光源遮挡物？

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

inline void GeometricObject::set_shadows(bool can_be_casted)
{
	this->shadows = can_be_casted;
}
#endif