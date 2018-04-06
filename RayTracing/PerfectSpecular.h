#ifndef __PERFECT_SPECULAR_H__
#define __PERFECT_SPECULAR_H__

#include "BRDF.h"
#include <glm/glm.hpp>

class PerfectSpecular :public BRDF
{
public:
	PerfectSpecular();
	~PerfectSpecular();

	void set_kr(float k);
	void set_color(const glm::vec3& c);
	void set_color(float r, float g, float b);

	virtual glm::vec3 f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const;
	virtual glm::vec3 sample_f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi) const;
	virtual glm::vec3 sample_f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi, float& pdf) const;

	virtual glm::vec3 rho(const ShadeRec& sr, const glm::vec3& wo) const;

private:
	float kr;
	glm::vec3 color;
};

inline void PerfectSpecular::set_kr(float k)
{
	kr = k;
}

inline void PerfectSpecular::set_cr(const glm::vec3& c)
{
	color = c;
}

inline void PerfectSpecular::set_cr(float r, float g, float b)
{
	color = glm::vec3(r, g, b);
}


#endif // !__PERFECT_SPECULAR_H__
