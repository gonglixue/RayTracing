#include "PerfectTransmitter.h"
// #include "ShadeRec.h"

PerfectTransmitter::PerfectTransmitter()
	:BTDF(),
	kt(0.0),
	ior(1.0)
{}

PerfectTransmitter::~PerfectTransmitter(void) {}

// total internal
bool
PerfectTransmitter::tir(const ShadeRec& sr) const {
	glm::vec3 wo(-sr.ray.d);
	float cos_thetai = glm::dot(sr.normal, wo);
	float eta = ior;

	if (cos_thetai < 0.0)
		eta = 1.0 / eta;

	return (1.0 - (1.0 - cos_thetai * cos_thetai) / (eta * eta) < 0.0);
}

glm::vec3 PerfectTransmitter::f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const 
{
	return BLACK;
}

glm::vec3
PerfectTransmitter::sample_f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wt) const 
{

	glm::vec3 n(sr.normal);
	float cos_thetai = glm::dot(n, wo);
	float eta = ior;

	if (cos_thetai < 0.0) {			// transmitted ray is outside     
		cos_thetai = -cos_thetai;
		n = -n;  					// reverse direction of normal
		eta = 1.0 / eta; 			// invert ior 
	}

	float temp = 1.0 - (1.0 - cos_thetai * cos_thetai) / (eta * eta);
	float cos_theta2 = sqrt(temp);
	wt = -wo / eta - (cos_theta2 - cos_thetai / eta) * n;

	// P570  Formula 27.9
	return kt / (eta * eta) / fabs(glm::dot(sr.normal, wt)) * WHITE;
}

glm::vec3
PerfectTransmitter::rho(const ShadeRec& sr, const glm::vec3& wo) const {
	return BLACK;
}

glm::vec3 PerfectTransmitter::sample_f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wt, float& pdf) const
{
	glm::vec3 n(sr.normal);
	float cos_thetai = glm::dot(n, wo);
	float eta = ior;

	if (cos_thetai < 0.0) {			// transmitted ray is outside     
		cos_thetai = -cos_thetai;
		n = -n;  					// reverse direction of normal
		eta = 1.0 / eta; 			// invert ior 
	}

	float temp = 1.0 - (1.0 - cos_thetai * cos_thetai) / (eta * eta);
	float cos_theta2 = sqrt(temp);
	wt = -wo / eta - (cos_theta2 - cos_thetai / eta) * n;

	pdf = fabs(glm::dot(sr.normal, wt));
	// P570  Formula 27.9
	return kt / (eta * eta) * WHITE;
}