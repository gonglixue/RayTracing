#ifndef __SPHERE_H__
#define __SPHERE_H__
#include "GeometricObject.h"


class Sphere :public GeometricObject
{
public:
	Sphere();
	Sphere(glm::dvec3 _center, double _r);
	Sphere(const Sphere& sphere);
	~Sphere();
	
	Sphere& operator= (const Sphere& sphere);

	void set_center(const glm::dvec3& _center);
	void set_center(double x, double y, double z);
	void set_radius(double _radius);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
	virtual bool shadow_hit(const Ray& ray, float& t) const;
	
	virtual glm::vec3 get_normal(const glm::vec3& point);
private:
	glm::dvec3 center;
	float radius;
	//static double kEpsilon;
};

inline void Sphere::set_center(const glm::dvec3& _center)
{
	center = _center;
}

inline void Sphere::set_center(double x, double y, double z)
{
	center = glm::dvec3(x, y, z);
}

inline void Sphere::set_radius(double _radius)
{
	radius = _radius;
}

#endif

