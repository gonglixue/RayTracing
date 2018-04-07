#ifndef __TRANSPARENT_H__
#define __TRANSPARENT_H__

#include "Phong.h"
#include "PerfectSpecular.h"
#include "PerfectTransmitter.h"

class Transparent :public Phong {
public:
	Transparent();
	~Transparent();

	void set_kr(float k) { reflective_brdf->set_kr(k); };
	void set_cr(const glm::vec3& color) { reflective_brdf->set_color(color); };
	void set_cr(float r, float g, float b){ reflective_brdf->set_color(r,g,b); };

	void set_ior(float eta) { specular_btdf->set_ior(eta); };
	void set_kt(float k) { specular_btdf->set_kt(k); };

	glm::vec3 shade(ShadeRec& s);
	glm::vec3 path_shade(ShadeRec& sr);
	//glm::vec3 area_light_shade(ShadeRec& sr);
	//glm::vec3 global_shade(ShadeRec& sr);
private:
	PerfectSpecular* reflective_brdf;
	PerfectTransmitter* specular_btdf;
};
#endif // !__TRANSPARENT_H__
