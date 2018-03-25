#ifndef __PHONG_H__
#define __PHONG_H__

#include "Material.h"
#include "Lambertian.h"
#include "GlossySpecular.h"

class Phong:public Material {
public:
	Phong();
	Phong(const Phong& phong_mat);
	Phong& operator= (const Phong& rhs);
	~Phong();

	void set_ka(float k);				// 环境光系数
	void set_kd(float k);				// 漫反射系数
	void set_cd(const glm::vec3& c);	// 设置材质颜色
	void set_cd(float r, float, float b);
	void set_cd(float c);
	void set_ks(float k);				// 镜面反射系数
	void set_exp(float e);

	virtual glm::vec3 shade(ShadeRec& sr);

protected:
	Lambertian* ambient_brdf;
	Lambertian* diffuse_brdf;
	GlossySpecular* specular_brdf;
};

inline void
Phong::set_ka(float k) {
	ambient_brdf->set_kd(k);
}

inline void 
Phong::set_kd(float k) {
	diffuse_brdf->set_kd(k);
}

inline void
Phong::set_cd(const glm::vec3& c)
{
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}

inline void
Phong::set_cd(float r, float g, float b) {
	ambient_brdf->set_cd(r, g, b);
	diffuse_brdf->set_cd(r, g, b);
}

inline void
Phong::set_cd(float c)
{
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}

inline void
Phong::set_ks(float k)
{
	specular_brdf->set_ks(k);
}

inline void
Phong::set_exp(float e) {
	specular_brdf->set_exp(e);
}

#endif // !__PHONG_H__
