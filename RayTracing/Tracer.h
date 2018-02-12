#ifndef __TRACER_H__
#define __TRACER_H__

#include "Constants.h"
#include "Ray.h"

class World;

class Tracer
{
public:
	Tracer();
	Tracer(World* _world_ptr);
	virtual ~Tracer();

	virtual glm::vec3 trace_ray(const Ray& ray) const;  // ���е�������һ��Ҫʵ�ֻ�����麯��?
	virtual glm::vec3 trace_ray(const Ray ray, const int depth) const;

protected:
	World* world_ptr;



};

#endif
