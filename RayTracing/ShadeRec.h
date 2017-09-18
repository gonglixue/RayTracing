#ifndef __SHADE_REC_H__
#define __SHADE_REC_H__

#include <glm\glm.hpp>
#include "World.h"

class ShadeRec {
public:
	bool		hit_an_object;		// if the ray hit an object
	glm::vec3	local_hit_point;	// world coordinates of hit point
	glm::vec3	normal;				// normal at hit point
	glm::vec3 color;
	World& w;						// world reference for shading
	
	ShadeRec(World& w);
	ShadeRec(const ShadeRec& sr);
	
	ShadeRec& operator= (const ShadeRec& rhs);

};

#endif