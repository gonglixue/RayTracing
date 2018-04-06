#include "PathTrace.h"
#include "World.h"
#include "ShadeRec.h"
#include "Material.h"

PathTrace::PathTrace()
	:Tracer()
{

}

PathTrace::PathTrace(World* _world_ptr)
	: Tracer(_world_ptr)
{

}

glm::vec3 PathTrace::trace_ray(const Ray& ray, const int depth) const
{
	if (depth > MAX_TRACE_DEPTH)
		return BLACK;

	else {
		ShadeRec sr(world_ptr->hit_objects(ray));

		if (sr.hit_an_object) {
			sr.depth = depth;
			sr.ray = ray;

			return sr.material_ptr->path_shade(sr);
		}
		else
			return world_ptr->background_color;
	}
}

// only used in Dielectrin material for color filtering
glm::vec3 PathTrace::trace_ray(const Ray& ray, double& tmin, const int depth) const
{
	if (depth > MAX_TRACE_DEPTH)
		return BLACK;
	else {
		ShadeRec sr(world_ptr->hit_objects(ray));

		if (sr.hit_an_object) {
			sr.depth = depth;
			sr.ray = ray;
			tmin = sr.t;     // required for colored transparency
			return (sr.material_ptr->path_shade(sr));
		}
		else {
			tmin = kHugeValue;
			return (world_ptr->background_color);
		}
	}
}
