#if 0
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


};

#endif // !__EMISSIVE_H__

#endif