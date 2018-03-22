#include "RayCast.h"
#include "World.h"
#include "ShadeRec.h"
#include "Material.h"

RayCast::RayCast(World* _world_ptr) :Tracer(_world_ptr)
{

}

RayCast::~RayCast(){}

glm::vec3 RayCast::trace_ray(const Ray ray, const int depth) const
{
	ShadeRec sr(world_ptr->hit_objects(ray));
	if (sr.hit_an_object) {
		sr.ray = ray;
		return (sr.material_ptr->shade(sr));
	}

	return world_ptr->background_color;
}