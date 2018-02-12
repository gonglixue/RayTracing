#ifndef __WORLD_H__
#define __WORLD_H__

#include "ViewPlane.h"
#include "Sphere.h"
#include "Tracer.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <glut.h>

class World {
public:
	World();
	~World();

	ViewPlane vp;
	glm::vec3 background_color;
	Sphere sphere_;
	Tracer* tracer_ptr;
	std::vector<GeometricObject*> objects;

	void build(const int width=200, const int height=200);
	void add_object(GeometricObject* object_ptr);
	ShadeRec hit_bare_bones_objects(const Ray& ray);
	void render_scene();
	

private:
	
	GLubyte* frame_buffer;
	void display_pixel(int row,
		int column,
		const glm::vec3& pixel_color);
	void open_window(const int hres, const int vres) const;
};

inline void World::add_object(GeometricObject* object_ptr) {
	objects.push_back(object_ptr);
}

#endif
