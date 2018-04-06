#ifndef __BRDF_H__
#define __BRDF_H__

#include "ShadeRec.h"
#include "Sampler.h"

class BRDF
{
public:
	BRDF();
	BRDF(const BRDF& brdf);
	BRDF& operator= (const BRDF& rhs);
	virtual ~BRDF();

	void set_sampler(Sampler* sampler_ptr);
	virtual glm::vec3
		f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const;
	virtual glm::vec3
		sample_f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi) const;
	// ��ײ���ϰ���������㷴�����wi��������Ӧ�ĸ���
	virtual glm::vec3
		sample_f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi, float& pdf) const;
	virtual glm::vec3
		rho(const ShadeRec& sr, const glm::vec3& wo) const;

protected:
	Sampler* sampler_ptr;

};

#endif // !__BRDF_H__
