#include "Tracer.h"

Tracer::Tracer()
	:world_ptr(NULL)
{}

Tracer::Tracer(World* _world_ptr)
	:world_ptr(_world_ptr)
{}

Tracer::~Tracer(void) {
	if (world_ptr) {
		delete world_ptr;
		world_ptr = NULL;
	}
}

glm::vec3 Tracer::trace_ray(const Ray& ray) const
{
	return BLACK;
}

glm::vec3 Tracer::trace_ray(const Ray ray, const int depth) const 
{
	return BLACK;
}