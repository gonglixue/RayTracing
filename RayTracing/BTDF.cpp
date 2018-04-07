#include "BTDF.h"

BTDF::BTDF(void) {}

BTDF::~BTDF(void) {}

glm::vec3
BTDF::f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const {
	return (BLACK);
}

glm::vec3
BTDF::sample_f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi) const {
	return (BLACK);
}

glm::vec3
BTDF::rho(const ShadeRec& sr, const glm::vec3& wo) const {
	return (BLACK);
}

bool BTDF::tir(const ShadeRec& sr) const {
	return false;
}