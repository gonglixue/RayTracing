#ifndef __WORLD_H__
#define __WORLD_H__

#include "ViewPlane.h"
#include "Sphere.h"
#include "Tracer.h"
#include "Pinhole.h"
#include "Light.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <glut.h>

class Camera;

class World {
public:
	World();
	~World();

	ViewPlane vp;
	glm::vec3 background_color;
	Sphere sphere_;
	Tracer* tracer_ptr;
	std::vector<GeometricObject*> objects;
	Light* ambient_ptr;
	std::vector<Light*> lights;

	void build(const int width=200, const int height=200);
	void add_object(GeometricObject* object_ptr);
	void add_light(Light* light_ptr);

	ShadeRec hit_objects(const Ray& ray);
	ShadeRec hit_bare_bones_objects(const Ray& ray);

	void render_scene();
	void render_perspective();

	const ViewPlane& get_viewplane() const { return vp; }
	const Tracer* get_tracer() const { return tracer_ptr; }
	void display_pixel(int row,
		int column,
		const glm::vec3& pixel_color);
	void draw_framebuffer()
	{
		glDrawPixels(vp.hres, vp.vres, GL_RGB, GL_UNSIGNED_BYTE, frame_buffer);
		glutSwapBuffers();
	}

	void set_camera(Camera* c_ptr);

private:
	
	GLubyte* frame_buffer;
	Camera* camera_ptr;
	void open_window(const int hres, const int vres) const;
};

inline void World::add_object(GeometricObject* object_ptr) {
	objects.push_back(object_ptr);
}

inline void World::set_camera(Camera* c_ptr)
{
	camera_ptr = c_ptr;
}

inline void World::add_light(Light* light_ptr)
{
	lights.push_back(light_ptr);
}

#endif
