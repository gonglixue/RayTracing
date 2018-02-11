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
	double ox = ray.o.x;
	double oy = ray.o.y;
	double oz = ray.o.z;
	double dx = ray.d.x;
	double dy = ray.d.y;
	double dz = ray.d.z;

	double tx_min, ty_min, tz_min;
	double tx_max, ty_max, tz_max;

	double a = 1.0 / dx;
	if (a >= 0) {
		tx_min = (x0_ - ox) * a;
		tx_max = (x1_ - ox) * a;
	}
	else {
		tx_min = (x1_ - ox) * a;
		tx_max = (x0_ - ox) * a;
	}

	double b = 1.0 / dy;
	if (b >= 0) {
		ty_min = (y0_ - oy) * b;
		ty_max = (y1_ - oy) * b;
	}
	else {
		ty_min = (y1_ - oy) * b;
		ty_max = (y0_ - oy) * b;
	}

	double c = 1.0 / dz;
	if (c >= 0) {
		tz_min = (z0_ - oz) * c;
		tz_max = (z1_ - oz) * c;
	}
	else {
		tz_min = (z1_ - oz) * c;
		tz_max = (z0_ - oz) * c;
	}

	double t0, t1;
	if (tx_min > ty_min)
		t0 = tx_min;
	else
		t0 = ty_min;

	if (tx_max < ty_max)
		t1 = tx_max;
	else
		t1 = ty_max;

	if (tz_max < t1)
		t1 = tz_max;

	return (t0<t1 && t1>kEpsilon);

}

bool BBox::inside(const glm::dvec3& p) const
{
	return (
		(p.x > x0_ && p.x < x1_) &&
		(p.y > y0_ && p.y < y1_) &&
		(p.z > z0_ && p.z < z1_)
		);
}