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
};

#endif // ! __LIGHT__
