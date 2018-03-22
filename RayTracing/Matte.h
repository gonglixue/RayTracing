#ifndef __MATTE_H__
#define __MATTE_H__

#include"Material.h"
#include "Lambertian.h"

// 环境光-漫反射，最简单的材质
class Matte :public Material {
public:
	Matte();
	Matte(const Matte& m);
	Matte& operator= (const Matte& rhs);
	~Matte();

	void set_ka(float k);
	void set_kd(float k);
	void set_cd(const glm::vec3& c);
	void set_cd(float r, float g, float b);
	void set_cd(float c);

	virtual glm::vec3 shade(ShadeRec& sr);
private:
	Lambertian* ambient_brdf;
	Lambertian* diffuse_brdf;
};

// ---------------------------------------------------------------- set_ka
// this sets Lambertian::kd
// there is no Lambertian::ka data member because ambient reflection
// is diffuse reflection

inline void
Matte::set_ka(float ka) {
	ambient_brdf->set_kd(ka);
}


// ---------------------------------------------------------------- set_kd
// this also sets Lambertian::kd, but for a different Lambertian object

inline void
Matte::set_kd(float kd) {
	diffuse_brdf->set_kd(kd);
}


// ---------------------------------------------------------------- set_cd

inline void
Matte::set_cd(const glm::vec3& c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}


// ---------------------------------------------------------------- set_cd

inline void
Matte::set_cd(float r, float g, float b) {
	ambient_brdf->set_cd(r, g, b);
	diffuse_brdf->set_cd(r, g, b);
}

// ---------------------------------------------------------------- set_cd

inline void
Matte::set_cd(float c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}
#endif // !__MATTE_H__
