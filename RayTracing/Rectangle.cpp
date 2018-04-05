#include "Rectangle.h"
#include "ShadeRec.h"
#include <stdio.h>
Rectangle::Rectangle()
	:GeometricObject(),
	p0(-1, 0, -1),
	a(0, 0, 2),
	b(2, 0, 0),
	a_len_squared(4.0),
	b_len_squared(4.0),
	normal(0, 1, 0),
	area(4.0),
	inv_area(0.25),
	sampler_ptr(NULL)
{}

Rectangle::Rectangle(const glm::vec3& _p0, const glm::vec3& _a, const glm::vec3& _b)
	:GeometricObject(),
	p0(_p0),
	a(_a),
	b(_b),
	a_len_squared(pow(glm::length(a), 2)),
	b_len_squared(pow(glm::length(b), 2)),
	area(glm::length(a) * glm::length(b)),
	inv_area(1.0 / area),
	sampler_ptr(NULL)
{
	normal = glm::cross(a, b);
	normal = glm::normalize(normal);
}

Rectangle::Rectangle(const glm::vec3& _p0, const glm::vec3& _a, const glm::vec3& _b, const glm::vec3& n)
	: GeometricObject(),
	p0(_p0),
	a(_a),
	b(_b),
	a_len_squared(pow(glm::length(a), 2)),
	b_len_squared(pow(glm::length(b), 2)),
	area(glm::length(a) * glm::length(b)),
	inv_area(1.0 / area),
	normal(n),
	sampler_ptr(NULL)
{
	normal = glm::normalize(n);
}

// copy constructor
Rectangle::Rectangle(const Rectangle& r)
	: GeometricObject(r),
	p0(r.p0),
	a(r.a),
	b(r.b),
	a_len_squared(r.a_len_squared),
	b_len_squared(r.b_len_squared),
	normal(r.normal),
	area(r.area),
	inv_area(r.inv_area)
{
	if (r.sampler_ptr) {
		// sampler_ptr = r.sampler_ptr->clone();
		printf("Rectangle copy constructor::Lack of the implementation of Sampler.clone\n");
		exit(1);
	}
	else  sampler_ptr = NULL;
}

Rectangle&
Rectangle::operator= (const Rectangle& rhs) {
	if (this == &rhs)
		return (*this);

	GeometricObject::operator=(rhs);

	p0 = rhs.p0;
	a = rhs.a;
	b = rhs.b;
	a_len_squared = rhs.a_len_squared;
	b_len_squared = rhs.b_len_squared;
	area = rhs.area;
	inv_area = rhs.inv_area;
	normal = rhs.normal;

	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	if (rhs.sampler_ptr) {
		// sampler_ptr = rhs.sampler_ptr->clone();
		printf("Rectangle operator=::Lack of the implementation of Sampler.clone\n");
		exit(1);
	}

	return (*this);
}

Rectangle::~Rectangle(void) {

	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
}

BBox
Rectangle::get_bounding_box(void) {
	double delta = 0.0001;

	return(BBox(fmin(p0.x, p0.x + a.x + b.x) - delta, fmax(p0.x, p0.x + a.x + b.x) + delta,
		fmin(p0.y, p0.y + a.y + b.y) - delta, fmax(p0.y, p0.y + a.y + b.y) + delta,
		fmin(p0.z, p0.z + a.z + b.z) - delta, fmax(p0.z, p0.z + a.z + b.z) + delta));
}

// if the ray hit the rectangle
bool
Rectangle::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {

	//double t = (p0 - ray.o) * normal / (ray.d * normal);
	double t = glm::dot(p0 - glm::vec3(ray.o), normal) / glm::dot(glm::vec3(ray.d), normal);

	if (t <= kEpsilon)
		return (false);

	glm::vec3 p = ray.o + t * ray.d;
	glm::vec3 d = p - p0;

	double ddota = glm::dot(d, a);

	if (ddota < 0.0 || ddota > a_len_squared)
		return (false);

	double ddotb = glm::dot(d, b);

	if (ddotb < 0.0 || ddotb > b_len_squared)
		return (false);

	tmin = t;
	sr.normal = normal;
	sr.local_hit_point = p;

	return (true);
}

void Rectangle::set_sampler(Sampler* sampler)
{
	sampler_ptr = sampler;
}

glm::vec3 Rectangle::sample()
{
	glm::vec2 sample_point = sampler_ptr->sample_unit_square();
	return (p0 + sample_point.x * a + sample_point.y*b);
}

glm::vec3 Rectangle::get_normal(const glm::vec3& p)
{
	return normal;
}

float Rectangle::pdf(const ShadeRec& sr)
{
	return inv_area;
}