#include "Whitted.h"
#include "World.h"

#include "ShadeRec.h"
#include "Material.h"

Whitted::Whitted()
	:Tracer()
{}

Whitted::Whitted(World* _world_ptr)
	:Tracer(_world_ptr)
{

}

Whitted::~Whitted()
{}

glm::vec3 Whitted::trace_ray(const Ray& ray, const int depth) const
{
	if (depth > MAX_TRACE_DEPTH)
		return BLACK;
	else {
		ShadeRec sr(world_ptr->hit_objects(ray));

		if (sr.hit_an_object)
		{
			sr.depth = depth;
			sr.ray = ray;
			return sr.material_ptr->shade(sr);
		}
		else
			return world_ptr->background_color;
	}
}

glm::vec3 Whitted::trace_ray(const Ray& ray, double& tmin, const int depth) const
{
	if (depth > MAX_TRACE_DEPTH)
		return BLACK;
	else {
		ShadeRec sr(world_ptr->hit_objects(ray));

		if (sr.hit_an_object)
		{
			sr.depth = depth;
			sr.ray = ray;
			tmin = sr.t;

			return sr.material_ptr->shade(sr);
		}
		else
			return world_ptr->background_color;
	}
}