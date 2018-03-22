#ifndef __RAY_CAST_H__
#define __RAY_CAST_H__

#include "Tracer.h"
class RayCast :public Tracer {
public:
	RayCast(World* _world_ptr);
	virtual ~RayCast();
	virtual glm::vec3 trace_ray(const Ray ray, const int depth) const;

};
#endif // !__RAY_CAST_H__
