#ifndef __MULTIPLE_OBJECTS_H__
#define __MULTIPLE_OBJECTS_H__

#include "Tracer.h"

class MultipleObjects :public Tracer
{
public:
	MultipleObjects(World* world_ptr);
	MultipleObjects();
	virtual ~MultipleObjects() {}
	virtual glm::vec3 trace_ray(const Ray& ray) const;
};

#endif // !__MULTIPLE_OBJECTS_H__
