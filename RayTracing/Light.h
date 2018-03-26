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
	virtual glm::vec3 get_direction(ShadeRec& sr) = 0;	// ��ײ��ָ���Դ

	virtual glm::vec3 L(ShadeRec& sr);

	virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const;
	void set_shadows(bool isOpen) { shadows = isOpen; }
	bool casts_shadows() { return shadows; }

protected:
	bool shadows;		// �ù�Դ�Ƿ��ͶӰ��Ӱ
};

#endif // ! __LIGHT__
