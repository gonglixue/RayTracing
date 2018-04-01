#ifndef __AREA_LIGHT_H__
#define __AREA_LIGHT_H__

#include "Light.h"
#include "Material.h"
#include "GeometricObject.h"

class AreaLight :public Light {
public:
	AreaLight();
	AreaLight(const AreaLight& alight);
	virtual ~AreaLight();
	AreaLight& operator= (const AreaLight& rhs);

	void set_object(GeometricObject* obj_ptr);
	virtual glm::vec3 get_direction(ShadeRec& s);
	virtual glm::vec3 L(ShadeRec& sr);

	virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const;
	virtual float G(const ShadeRec& sr) const;
	virtual float pdf(const ShadeRec& sr) const;
private:
	GeometricObject* object_ptr;
	Material* material_ptr;	// will be an emissive material
	glm::vec3 sample_point;
	glm::vec3 light_normal;	// assigned in get_direction - which therefor can't be const for any light
	glm::vec3 wi;

};

inline void AreaLight::set_object(GeometricObject* obj_ptr)
{
	this->object_ptr = obj_ptr;
	material_ptr = object_ptr->get_material();
}
#endif // !__AREA_LIGHT_H__
