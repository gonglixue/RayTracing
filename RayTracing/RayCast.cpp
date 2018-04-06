#include "RayCast.h"
#include "World.h"
#include "ShadeRec.h"
#include "Material.h"

RayCast::RayCast(World* _world_ptr) :Tracer(_world_ptr)
{

}

RayCast::~RayCast(){}


// ray casting for other lights
glm::vec3 RayCast::trace_ray(const Ray& ray, const int depth) const
{
	ShadeRec sr(world_ptr->hit_objects(ray));
	if (sr.hit_an_object) {
		sr.ray = ray;
		//printf("[hit]:ray.o(%f, %f, %f), ray.dir(%f,%f,%f)\n", ray.o.x, ray.o.y, ray.o.z, ray.d.x, ray.d.y, ray.d.z);
		return (sr.material_ptr->shade(sr));
		// return sr.color;
	}
	//printf("no hit\n");

	return world_ptr->background_color;
}


/*
glm::vec3 RayCast::trace_ray(const Ray ray, const int depth) const
{
	ShadeRec sr(world_ptr->hit_objects(ray));
	if (sr.hit_an_object)
	{
		sr.ray = ray;
		return (sr.material_ptr->area_light_shade(sr));
	}

	return world_ptr->background_color;
}
*/

