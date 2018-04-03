#include "GlossySpecular.h"
#include "Jittered.h"

GlossySpecular::GlossySpecular()
	:BRDF(),
	ks(1.0),
	specular_color(1.0)
	//sampler(NULL)
{

}

GlossySpecular::GlossySpecular(const GlossySpecular& gs)
	:BRDF(gs),
	ks(gs.ks),
	specular_color(gs.specular_color),
	exp(gs.exp)
{
	printf("CopyConstructor of GlossySpecular: Error\n");
}

GlossySpecular::~GlossySpecular()
{
}

GlossySpecular* GlossySpecular::clone() const
{
	return (new GlossySpecular(*this));
}

void GlossySpecular::set_sampler(Sampler* sp, float _exp)
{
	sampler_ptr = sp;
	//exp = _exp;
	sampler_ptr->map_samples_to_hemisphere(exp);
}

void GlossySpecular::set_samples(int samples_num, float exp)
{
	sampler_ptr = new Jittered(samples_num);
	sampler_ptr->map_samples_to_hemisphere(exp);
}

// no sampling here: just use the Phong formula
// this is used for direct illumination only
glm::vec3 GlossySpecular::f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi) const
{
	glm::vec3 L(0, 0, 0);
	float ndotwi = glm::dot(sr.normal, wi);
	
	// reflection vector
	glm::vec3 r = -wi + 2.0f * ndotwi * sr.normal;
	float rdotwo = glm::dot(r, wo);

	if (rdotwo > 0.0)
		L = powf(rdotwo, exp) * ks * specular_color;

	return L;
}


// this is used for indirect illumination
glm::vec3 GlossySpecular::sample_f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi, float& pdf) const
{
	float ndotwo = glm::dot(sr.normal, wo);
	glm::vec3 r = -wo + 2.0f * ndotwo * sr.normal;

	glm::vec3 w = r;
	glm::vec3 u = glm::cross(glm::vec3(0.00424, 1, 0.00764), w);
	u = glm::normalize(u);
	glm::vec3 v = glm::cross(u, w);

	glm::vec3 sp = sampler_ptr->sample_hemisphere();
	wi = sp.x * u + sp.y * v + sp.z * w;

	if (glm::dot(sr.normal, wi) < 0.0)			// reflected ray is below tangent plane
		wi = -sp.x * u - sp.y * v + sp.z * w;

	float phong_lobe = pow(glm::dot(r, wi), exp);
	pdf = phong_lobe * glm::dot(sr.normal, wi);

	return (ks * phong_lobe * specular_color);
}

glm::vec3 GlossySpecular::rho(const ShadeRec& sr, const glm::vec3& wo)const
{
	return BLACK;
}

