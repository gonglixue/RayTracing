#ifndef __WORLD_H__
#define __WORLD_H__

#include "ViewPlane.h"
#include "Sphere.h"
#include "Tracer.h"

class World {
public:
	World();
	~World();

	ViewPlane vp;
	Sphere sphere;
	Tracer* tracer_ptr;

	void build();
	void render_scene() const;
	void open_window(const int hres, const int vres) const;

	void display_pixel(const int row,
		const int column,
		const glm::dvec3& pixel_color) const;
private:
	glm::vec3 background_color;
};

#endif
