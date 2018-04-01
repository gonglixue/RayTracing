#ifndef  __LIGHT_H__
#define  __LIGHT_H__

#include "Ray.h"

class ShadeRec;

class Light
{
public:
	Light();
	Light(const Light& ls);
	Light& operator= (const Light& rhs);

	virtual ~Light(void);
	virtual glm::vec3 get_direction(ShadeRec& sr) = 0;	// 碰撞点指向光源

	virtual glm::vec3 L(ShadeRec& sr);

	virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const;	// sr是否能看见光源
	void set_shadows(bool isOpen) { shadows = isOpen; }
	bool casts_shadows() { return shadows; }

	virtual float G(const ShadeRec& sr) const;
	virtual float pdf(const ShadeRec& sr) const;
protected:
	bool shadows;		// 该光源是否会投影阴影
};

#endif // ! __LIGHT__
