#if 1
#ifndef __EMISSIVE_H__
#define __EMISSIVE_H__
#include "Material.h"

// �Է�����ʡ����������䷽���޹أ�Ҳ���ᷴ����ߣ����Բ�����BRDF����
class Emissive :public Material
{
private:
	float ls;	// radiance scale factor
	glm::vec3 color;

public:
	Emissive();
	Emissive(const Emissive& emissive_mat);
	~Emissive();
	Emissive& operator= (const Emissive& emissive_mat);		// ?

	void set_radiance(float ls);
	void set_color(float r, float g, float b);
	void set_color(const glm::vec3& color_);

	virtual glm::vec3 get_Le(ShadeRec& sr) const;
	virtual glm::vec3 shade(ShadeRec& sr);
	virtual glm::vec3 area_light_shade(ShadeRec& sr);
	virtual glm::vec3 path_shade(ShadeRec& sr);
	virtual glm::vec3 global_shade(ShadeRec& sr);


};

inline void Emissive::set_radiance(const float _ls) {
	ls = _ls;
}

inline void Emissive::set_color(float r, float g, float b) {
	color = glm::vec3(r, g, b);
}

inline void Emissive::set_color(const glm::vec3& c)
{
	color = c;
}

#endif // !__EMISSIVE_H__

#endif