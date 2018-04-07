#ifndef __BTDF__
#define __BTDF__

#include <math.h>

#include "Constants.h"
#include "ShadeRec.h"

class BTDF {
public:

	BTDF(void);

	virtual
		~BTDF(void);

	virtual glm::vec3
		f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const;

	virtual glm::vec3
		sample_f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wt) const;

	virtual glm::vec3
		rho(const ShadeRec& sr, const glm::vec3& wo) const;

	virtual bool tir(const ShadeRec& sr) const;
};

#endif