#include "MultipleObjects.h"
#include "World.h"
#include "ShadeRec.h"

MultipleObjects::MultipleObjects(World* world_ptr)
	:Tracer(world_ptr)
{

}

MultipleObjects::MultipleObjects()
	:Tracer()
{}

glm::vec3 MultipleObjects::trace_ray(const Ray& ray) const
{
	ShadeRec sr(world_ptr->hit_bare_bones_objects(ray));

	if (sr.hit_an_object)
		return sr.color;
	else
		return world_ptr->background_color;
}