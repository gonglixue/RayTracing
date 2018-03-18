#ifndef __PINHOLE_H__
#define __PINHOLE_H__

#include "World.h"
#include "Camera.h"
#include <glm/glm.hpp>

class Pinhole:public Camera {
public:
	Pinhole();
	Pinhole(const Pinhole& ph);

	Pinhole& operator= (const Pinhole& rhs);

	virtual ~Pinhole();

	void set_view_distance(float vpd) {
		d = vpd;
	}
	void set_zoom(float zoom_factor) { zoom = zoom_factor; }

	glm::dvec3 get_direction(const glm::vec2 p) const;
	virtual void render_scene(World& w);

private:
	float d;		// view plane distance
	float zoom;		// zoom factor
		
};

#endif // !__PINHOLE_H__
