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
	void set_shadows(bool isOpen);

	virtual glm::vec3 get_Le(ShadeRec& sr) const;
	virtual glm::vec3 area_light_shade(ShadeRec& sr);
	virtual glm::vec3 path_shade(ShadeRec& sr);
	virtual void set_sampler(Sampler* sampler_ptr);
	virtual glm::vec3 global_shade(ShadeRec& sr);
protected:
	Material& operator= (const Material& rhs);
	bool shadows;
};

#endif // !__MATERIAL_H__
