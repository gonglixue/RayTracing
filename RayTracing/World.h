#ifndef __WORLD_H__
#define __WORLD_H__

#include "ViewPlane.h"
#include "Sphere.h"
#include "Tracer.h"
#include <glut.h>

class World {
public:
	World();
	~World();

	ViewPlane vp;
	Sphere sphere;
	Tracer* tracer_ptr;

	void build();
	void render_scene();
	void open_window(const int hres, const int vres) const;

	void display_pixel(int row,
		int column,
		const glm::vec3& pixel_color);
private:
	glm::vec3 background_color;
	GLubyte* frame_buffer;
};

#endif
