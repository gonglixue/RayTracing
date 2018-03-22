#ifndef __SHADE_REC_H__
#define __SHADE_REC_H__

#include <glm\glm.hpp>
#include "World.h"

class Material;

class ShadeRec {
public:
	bool		hit_an_object;		// if the ray hit an object
	Material* material_ptr;			// �������Ĳ���
	glm::vec3	local_hit_point;	// ??
	glm::vec3 hit_point;			// world coordinates of hit point
	glm::vec3	normal;				// normal at hit point
	glm::vec3 color;				// ֻ�ڵ�������ʹ��
	World& w;						// world reference for shading
	Ray ray;
	int depth;
	double t;						// ray parameter
	float u, v;						// texture coordinate
	// glm::vec3 dir;
	
	ShadeRec();
	ShadeRec(World& w);
	ShadeRec(const ShadeRec& sr);
	
	ShadeRec& operator= (const ShadeRec& rhs);

};

#endif