#ifndef __COMPOUND_H__
#define __COMPOUND_H__

#include <vector>
#include "GeometricObject.h"

class Compound :public GeometricObject
{
public:
	Compound();
	Compound(const Compound& c);
	~Compound();
	Compound& operator= (const Compound& rhs);

	virtual void set_material(Material* material_ptr);
	virtual void add_object(GeometricObject* object_ptr);
	int get_num_objects();

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& s) const;
	virtual bool shadow_hit(const Ray& ray, float& t) const;

protected:
	std::vector<GeometricObject*> objects;
private:
	void delete_objects();
	void copy_objects(const std::vector<GeometricObject*>& rhs_objects);

	
};

inline int Compound::get_num_objects()
{
	return objects.size();
}

#endif // !__COMPOUND_H__
