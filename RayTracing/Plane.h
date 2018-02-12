#ifndef __PLANE_H__
#define __PLANE_H__
#include "GeometricObject.h"
class Plane : public GeometricObject
{
public:
	Plane(void);
	Plane(const glm::dvec3 p, const glm::dvec3 n);
	Plane(const Plane& plane);
	virtual ~Plane();
	
	Plane& operator= (const Plane& rhs);
	

	virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const;
private:
	glm::dvec3 point;	//平面上的一个已知点
	glm::dvec3 normal;	//平面法线

	// for shadows and secondary rays
	// static const double kEpsilon;
};

#endif
