#ifndef __REFLECTIVE_H__
#define __REFLECTIVE_H__

#include "Phong.h"
#include "PerfectSpecular.h"

class Reflective :public Phong
{
public:
	Reflective();
	~Reflective();

	void set_kr(float k);
	void set_color(const glm::vec3& c);
	void set_color(float r, float g, float b);

	virtual glm::vec3 shade(ShadeRec& s);
	virtual glm::vec3 area_light_shade(ShadeRec& sr);
	virtual glm::vec3 path_shade(ShadeRec& sr);
	virtual glm::vec3 global_shade(ShadeRec& sr);

private:
	PerfectSpecular* reflective_brdf;

};

inline void 
Reflective::set_kr(float k)
{
	this->reflective_brdf->set_kr(k);
}

inline void 
Reflective::set_color(const glm::vec3& c)
{
	reflective_brdf->set_color(c);
}

inline void 
Reflective::set_color(float r, float g, float b)
{
	reflective_brdf->set_color(r, g, b);
}

#endif // !__REFLECTIVE_H__
