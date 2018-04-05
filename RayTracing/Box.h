#ifndef __BOX_H__
#define __BOX_H__
#include "GeometricObject.h"

class Box :public GeometricObject
{
public:
	Box(void);

	Box(const double x0, const double x1,
		const double y0, const double y1,
		const double z0, const double z1);

	Box(const glm::vec3 p0, const glm::vec3 p1);

	Box(const Box& bbox);

	virtual Box* clone(void) const;

	Box& operator= (const Box& rhs);

	~Box(void);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

	glm::vec3 get_normal(const int face_hit) const;

private:
	double x0, x1, y0, y1, z0, z1;
};
#endif // !__BOX_H__
