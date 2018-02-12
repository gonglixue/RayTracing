#ifndef __SINGLE_SPHERE_H__
#define __SINGLE_SPHERE_H__

#include "Tracer.h"

class SingleSphere :public Tracer
{
public:
	SingleSphere();
	SingleSphere(World* _world_ptr);

	virtual ~SingleSphere();
	virtual glm::vec3 trace_ray(const Ray& ray) const;
};

#endif // !__SINGLE_SPHERE_H__
