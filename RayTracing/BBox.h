#ifndef __BBOX_H__
#define __BBOX_H__

#include "Ray.h"
#include <glm/glm.hpp>

class BBox {
public:
	double x0_, x1_, y0_, y1_, z0_, z1_;
	BBox();
	BBox(double x0, double x1,
		double y0, double y1,
		double z0, double z1);
	BBox(const glm::dvec3& p0, const glm::dvec3& p1);
	BBox(const BBox& bbox);

	BBox& operator= (const BBox& rhs);

	~BBox();

	bool hit(const Ray& ray) const;
	bool inside(const glm::dvec3& point) const;

};

#endif