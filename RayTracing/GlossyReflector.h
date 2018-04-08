#ifndef __GLOSSY_REFLECTIVE_H__
#define __GLOSSY_REFLECTIVE_H__

#include "Phong.h"
#include "GlossySpecular.h"

class GlossyReflector :public Phong
{
public:
	GlossyReflector();
	~GlossyReflector();

	void set_samples(int num_samples, float exp);
	void set_kr(float k);
	void set_cr(const glm::vec3& c);
	void set_cr(float r, float g, float b);
	void set_exponent(float exp);

	virtual glm::vec3 path_shade(ShadeRec& sr);

private:
	GlossySpecular* glossy_specular_brdf;
};

inline void GlossyReflector::set_samples(int num_samples, float exp)
{
	glossy_specular_brdf->set_samples(num_samples, exp);
}

inline void
GlossyReflector::set_kr(float k) {
	glossy_specular_brdf->set_ks(k);
}

inline void GlossyReflector::set_cr(const glm::vec3& c) {
	glossy_specular_brdf->set_specular_color(c);
}

inline void
GlossyReflector::set_exponent(float exp) {
	glossy_specular_brdf->set_exp(exp);
}

inline void GlossyReflector::set_cr(float r, float g, float b) {
	glossy_specular_brdf->set_specular_color(r, g, b);
}
#endif // !__GLOSSY_REFLECTIVE_H__
