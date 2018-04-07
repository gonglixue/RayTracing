#ifndef __PERFECT_TRANSMITTER_H__
#define __PERFECT_TRANSMITTER_H__

#include "BTDF.h"

class PerfectTransmitter :public BTDF{
public:
	PerfectTransmitter();
	~PerfectTransmitter();
	
	//投射系数，投射通量的比例
	void set_kt(float k) { kt = k; };
	void set_ior(float eta){ ior = eta; };
	bool tir(const ShadeRec& sr) const;

	virtual glm::vec3 f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const;
	virtual glm::vec3 sample_f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wt) const;
	virtual glm::vec3 sample_f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wt, float& pdf) const;
	virtual glm::vec3 rho(const ShadeRec& sr, const glm::vec3& wo) const;

private:
	float kt;		// 投射系数
	float ior;		// index of refraction

};
#endif // !__PERFECT_TRANSMITTER_H__
