#ifndef __SPHERE_H__
#define __SPHERE_H__
#include "GeometricObject.h"
class Sphere:public GeometricObject
{
public:
	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
private:
	glm::dvec3 center;
	float radius;
	static double kEpsilon;
};
#endif

