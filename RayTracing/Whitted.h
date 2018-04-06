#ifndef __WHITTED_H__
#define __WHITTED_H__

#include "Tracer.h"

class Whitted :public Tracer
{
public:
	Whitted();
	Whitted(World* _world_ptr);
	virtual ~Whitted();

	virtual glm::vec3 trace_ray(const Ray& ray, const int depth) const;
	virtual glm::vec3 trace_ray(const Ray& ray, double& tmin, const int depth) const;
};

#endif // !__WHITTED_H__
