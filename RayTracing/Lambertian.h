#ifndef  __LAMBERTIAN_H__
#define  __LAMBERTIAN_H__

#include "BRDF.h"

class Lambertian :public BRDF
{
public:
	Lambertian();
	Lambertian(const Lambertian& lamb);
	Lambertian& operator= (const Lambertian& rhs);
	virtual ~Lambertian();

	virtual glm::vec3 f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi) const;
	// virtual glm::vec3 sample_f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi) const;
	virtual glm::vec3 sample_f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi, float& pdf) const;
	virtual glm::vec3 rho(const ShadeRec& sr, const glm::vec3& wo) const;

	void set_ka(float ka);
	void set_kd(float kd);
	void set_cd(const glm::vec3& c);
	void set_cd(float r, float g, float b);
	void set_cd(float c);

private:
	float kd;
	glm::vec3 cd;	// ÑÕÉ«

};

inline void 
Lambertian::set_ka(float k)
{
	kd = k;
}

inline void 
Lambertian::set_kd(float k)
{
	kd = k;
}

inline void 
Lambertian::set_cd(const glm::vec3& c)
{
	cd = c;
}

inline void 
Lambertian::set_cd(float r, float g, float b)
{
	cd = glm::vec3(r, g, b);
}

inline void
Lambertian::set_cd(float c)
{
	cd = glm::vec3(c, c, c);
}

#endif // ! __LAMBERTIAN_H__
