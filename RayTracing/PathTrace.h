#ifndef __PATH_TRACE_H__
#define __PATH_TRACE_H__

#include "Tracer.h"

class PathTrace :public Tracer
{
public:
	PathTrace();
	PathTrace(World* _world_ptr);

	virtual glm::vec3 trace_ray(const Ray& ray, const int depth) const;
	virtual glm::vec3 trace_ray(const Ray& ray, double& tmin, const int depth) const;
};


#endif // !__PATH_TRACE_H__
