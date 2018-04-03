#ifndef __GLOSSY_SPECULAR_H__
#define __GLOSSY_SPECULAR_H__
#include "BRDF.h"
#include "ShadeRec.h"
#include "Sampler.h"

class GlossySpecular :public BRDF
{
public:
	GlossySpecular();
	~GlossySpecular();
	GlossySpecular(const GlossySpecular& gs);
	virtual GlossySpecular* clone() const;

	virtual glm::vec3 f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi) const;
	//virtual glm::vec3
	//	sample_f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const;
	virtual glm::vec3
		sample_f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi, float& pdf) const;
	virtual glm::vec3
		rho(const ShadeRec& sr, const glm::vec3& wo) const;

	void set_ks(float _ks) { ks = _ks; };
	void set_exp(float _exp) { exp = _exp; }
	void set_specular_color(const glm::vec3& c) { specular_color = c; }
	void set_specular_color(float r, float g, float b) { specular_color = glm::vec3(r, g, b); }

	void set_sampler(Sampler* sp, float exp);   			// any type of sampling
	void set_samples(const int num_samples, float exp); 	// multi jittered sampling

	// void set_normal(const glm::vec3& n);
private:
	float ks;
	glm::vec3 specular_color;
	float exp;	// specular exponent
	Sampler *sampler;			//??


};

#endif // !__GLOSSY_SPECULAR_H__
