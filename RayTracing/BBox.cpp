#include "BBox.h"
#include "Constants.h"

BBox::BBox(void)
	:x0_(-1), x1_(1), y0_(-1), y1_(1), z0_(-1), z1_(1)
{}

BBox::BBox(double _x0, double _x1,
	double _y0, double _y1,
	double _z0, double _z1)
	:x0_(_x0), y0_(_y0), z0_(_z0),
	x1_(_x1), y1_(_y1), z1_(_z1)
{

}

BBox::BBox(const glm::dvec3& p0, const glm::dvec3& p1)
	:x0_(p0.x), x1_(p1.x),
	y0_(p0.y), y1_(p1.y),
	z0_(p0.z), z1_(p1.z)

{
}

BBox::BBox(const BBox& bbox)
	:x0_(bbox.x0_), x1_(bbox.x1_),
	y0_(bbox.y0_), y1_(bbox.y1_),
	z0_(bbox.z0_), z1_(bbox.z1_)
{}

BBox& BBox::operator= (const BBox& rhs)
{
	if (this == &rhs)
		return (*this);
	x0_ = rhs.x0_;
	x1_ = rhs.x1_;
	y0_ = rhs.y0_;
	y1_ = rhs.y1_;
	z0_ = rhs.z0_;
	z1_ = rhs.z1_;

	return (*this);
}

BBox::~BBox() {}

bool BBox::hit(const Ray& ray) const
{

}