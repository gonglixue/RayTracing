#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "World.h"
#include "ShadeRec.h"

class Material
{
public:
	Material();
	Material(const Material& material);
	virtual ~Material();

	virtual glm::vec3 shade(ShadeRec& sr);
protected:
	Material& operator= (const Material& rhs);
};

#endif // !__MATERIAL_H__
