#ifndef __WORLD_H__
#define __WORLD_H__

#include "ViewPlane.h"
#include "Sphere.h"
#include "Tracer.h"
#include <stdlib.h>
#include <stdio.h>
#include <glut.h>

class World {
public:
	World();
	~World();

	ViewPlane vp;
	Sphere sphere_;
	Tracer* tracer_ptr;

	void build(const int width=200, const int height=200);
	void render_scene();
	

private:
	glm::vec3 background_color;
	GLubyte* frame_buffer;
	void display_pixel(int row,
		int column,
		const glm::vec3& pixel_color);
	void open_window(const int hres, const int vres) const;
};

#endif
