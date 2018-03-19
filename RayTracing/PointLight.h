#ifndef __POINT_LIGHT_H__
#define __POINT_LIGHT_H__

#include "Light.h"

class PointLight :public Light
{
public:
	PointLight();
	PointLight(const PointLight& p_light);
	PointLight& operator= (const PointLight& rhs);
	virtual ~PointLight();

	void scale_radiance(float scale);

	void set_color(float r, float g, float b);
	void set_color(const glm::vec3& c);

	void set_location(glm::vec3& light_pos);
	void set_location(float x, float y, float z);
	glm::vec3 get_location();

	virtual glm::vec3 get_direction(ShadeRec& s);
	virtual glm::vec3 L(ShadeRec& s);

private:
	float ls;
	glm::vec3 color;
	glm::vec3 location;
};

inline void PointLight::scale_radiance(float scale)
{
	ls = scale;
}

inline void PointLight::set_color(float r, float g, float b) {
	color = glm::vec3(r, g, b);
}

inline void PointLight::set_color(const glm::vec3& c) {
	color = c;
}

inline void PointLight::set_location(glm::vec3& light_pos)
{
	location = light_pos;
}

inline glm::vec3 PointLight::get_location() {
	return location;
}


#endif // !__POINT_LIGHT_H__
