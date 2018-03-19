#ifndef __AMBIENT_H__
#define __AMBIENT_H__

#include "Light.h"

class Ambient :public Light
{
public:
	Ambient();
	Ambient(const Ambient& a);
	Ambient& operator= (const Ambient& rhs);
	virtual ~Ambient();

	void scale_radiance(float b);
	
	void set_color(float c);
	void set_color(const glm::vec3& c);
	void set_color(float r, float g, float b);

	virtual glm::vec3 get_direction(ShadeRec& s);
	virtual glm::vec3 L(ShadeRec& s);

private:
	float ls;		// scale
	glm::vec3 color;
};

inline void Ambient::scale_radiance(float b)
{
	ls = b;
}

inline void Ambient::set_color(float c)
{
	color = glm::vec3(c, c, c);
}

inline void Ambient::set_color(const glm::vec3& c)
{
	color = c;
}

inline void Ambient::set_color(float r, float g, float b)
{
	color = glm::vec3(r, g, b);
}

#endif // !__AMBIENT_H__
