#ifndef __RAY_H__
#define __RAY_H__

#include<glm\glm.hpp>

class Ray
{
public:
	glm::vec3 o; // position of light source
	glm::vec3 d; // direction of light
	Ray(void);
	Ray(const glm::vec3& origin, const glm::vec3& dir);
	Ray(const Ray& ray);

	Ray& operator= (const Ray& rhs);
	~Ray(void);
};

#endif