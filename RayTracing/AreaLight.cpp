#include "AreaLight.h"

AreaLight::AreaLight()
	:Light(),
	object_ptr(NULL),
	material_ptr(NULL)
{

}

AreaLight::AreaLight(const AreaLight& al)
	:Light(al)
{
	if (al.object_ptr) {
		//object_ptr = new GeometricObject((*al.object_ptr));	// 可是不知道al.object_ptr派生类类型？
		printf("Error: clone not implemented in AreaLight\n");
		exit(1);
	}
	else
		object_ptr = NULL;

	if (al.material_ptr) {
		//material_ptr = new Material((*al.material_ptr));
		printf("Error: clone not implemented in AreaLight\n");
		exit(1);
	}
	else
		material_ptr = NULL;
}

AreaLight::~AreaLight(void)
{
	if (object_ptr) {
		delete object_ptr;
		object_ptr = NULL;
	}
	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}
}

AreaLight& AreaLight::operator= (const AreaLight& rhs)
{
	if (this == &rhs)
		return (*this);

	Light::operator=(rhs);

	if (object_ptr)
	{
		delete object_ptr;
		object_ptr = NULL;
	}

	if (rhs.object_ptr)
		object_ptr = new GeometricObject((*rhs.object_ptr));

	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}
	if (rhs.material_ptr)
		material_ptr = new Material(*rhs.material_ptr);

	return (*this);
}

// 返回着色点与采样点之间的方向向量
glm::vec3 AreaLight::get_direction(ShadeRec& sr)
{
	sample_point = object_ptr->sample();	// used in the G function
	light_normal = object_ptr->get_normal(sample_point);
	wi = sample_point - sr.hit_point;
	wi = glm::normalize(wi);

	return wi;
}

glm::vec3 AreaLight::L(ShadeRec& sr)
{
	float ndotd = glm::dot(-light_normal, wi);
	if (ndotd > 0.0)
		return material_ptr->get_Le(sr);
	else
		return BLACK;
}

bool AreaLight::in_shadow(const Ray& ray, const ShadeRec& sr) const
{
	float t;
	int num_objects = sr.w.objects.size();
	float ts = glm::dot((sample_point - glm::vec3(ray.o)), glm::vec3(ray.d));

	for(int j = 0; j < num_objects; j++)
		if (sr.w.objects[j]->shadow_hit(ray, t) && (t < ts))
			return true;

	return false;
}

float AreaLight::G(const ShadeRec& sr) const
{
	// wi is sr.hit_point to area light's sampler_point
	float ndotd = glm::dot(-light_normal, wi);
	float d2 = glm::distance(sample_point, sr.hit_point);

	return ndotd / (d2*d2);
}

float AreaLight::pdf(const ShadeRec& sr) const
{
	return object_ptr->pdf(sr);
}