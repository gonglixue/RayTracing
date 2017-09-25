#ifndef __PLANE_H__
#define __PLANE_H__
#include "GeometricObject.h"
class Plane : public GeometricObject
{
public:
	Plane(void);
	Plane(const glm::vec3 p, const glm::vec3 n);
	virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const;
private:
	glm::dvec3 point;
	glm::dvec3 normal;
	static const double kEpsilon;
};

#endif
