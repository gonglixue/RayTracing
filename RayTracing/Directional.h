#ifndef __DERECTIONAL_H__
#define __DERECTIONAL_H__

#include "Light.h"
#include "World.h"
#include "ShadeRec.h"

class Directional :public Light
{
public:
	Directional();
	Directional(const Directional& dl);
	Directional& operator= (const Directional& rhs);
	virtual ~Directional();

	void scale_radiance(float b);
	void set_color(float c);
	void set_color(float r, float g, float b);
	void set_color(const glm::vec3 c);
	
	void set_direction(glm::vec3 d);
	void set_direction(float dx, float dy, float dz);
	
	virtual glm::vec3 get_direction(ShadeRec& sr);
	virtual glm::vec3 L(ShadeRec& sr);

	virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const;

private:
	float ls;			// scale radiance
	glm::vec3 color;
	glm::vec3 dir;
};

inline void
Directional::scale_radiance(float b)
{
	ls = b;
}

inline void
Directional::set_color(float c)
{
	color = glm::vec3(c);
}

inline void
Directional::set_color(float r, float g, float b) {
	color = glm::vec3(r, g, b);
}

inline void 
Directional::set_color(glm::vec3 c) {
	color = c;
}

inline void
Directional::set_direction(glm::vec3 d)
{
	dir = d;
}

inline void
Directional::set_direction(float dx, float dy, float dz) {
	dir = glm::vec3(dx, dy, dz);
	dir = glm::normalize(dir);
}

#endif // !__DRECTIONAL_H__
