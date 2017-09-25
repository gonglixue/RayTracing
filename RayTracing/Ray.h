#ifndef __RAY_H__
#define __RAY_H__

#include<glm\glm.hpp>

class Ray
{
public:
	glm::dvec3 o; // position of light source
	glm::dvec3 d; // direction of light
	Ray(void);
	Ray(const glm::dvec3& origin, const glm::dvec3& dir);
	Ray(const Ray& ray);

	Ray& operator= (const Ray& rhs);
	~Ray(void);
};

#endif