#ifndef __CONCAVE_SPHERE_H__
#define	__CONCAVE_SPHERE_H__

#include "Sphere.h"

class ConcaveSphere :public Sphere
{
public:
	ConcaveSphere();
	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
	virtual bool shadow_hit(const Ray& ray, float& t) const
	{
		return false;
	};
};
#endif // !__CONCAVE_SPHERE_H--
