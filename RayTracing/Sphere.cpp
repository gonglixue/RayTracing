#include "Sphere.h"
#include "ShadeRec.h"

Sphere::Sphere() 
	:GeometricObject(),
	center(0,0,0),
	radius(1.0)
{}

Sphere::Sphere(const glm::dvec3 _center, double _radius)
	:GeometricObject(),
	center(_center),
	radius(_radius)
{}

Sphere::Sphere(const Sphere& sphere)
	:GeometricObject(sphere),
	center(sphere.center),
	radius(sphere.radius)
{}

Sphere::~Sphere()
{}

Sphere& Sphere::operator= (const Sphere& sphere)
{
	if (this == &sphere)
		return (*this);

	GeometricObject::operator= (sphere);
	
	center = sphere.center;	//?
	radius = sphere.radius;

	return (*this);
}

bool Sphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
{
	double t;
	glm::dvec3 temp = ray.o - center;
	double a = glm::dot(ray.d, ray.d);
	double b = 2.0 * glm::dot(temp, ray.d);
	double c = glm::dot(temp, temp) - radius * radius;
	double disc = b*b - 4 * a*c;	// delta

	if (disc < 0.0)	// 无解，不相交
		return false;
	else {
		double e = sqrt(disc);
		double denom = 2 * a;
		t = (-b - e) / denom;  // smaller root

		if (t > kEpsilon) {
			tmin = t;
			sr.normal = (temp + t*ray.d) / (double)radius;
			sr.normal = glm::normalize(sr.normal);
			sr.local_hit_point = ray.o + t * ray.d;
			//sr.hit_point = sr.local_hit_point;			// Lg: treat hit_point as local_hit_point;
			return true;
		}

		// larger root
		t = (-b + e) / denom;
		if (t > kEpsilon)
		{
			tmin = t;
			sr.normal = (temp + t*ray.d) / (double)radius;
			sr.normal = glm::normalize(sr.normal);
			sr.local_hit_point = ray.o + t*ray.d;
			//sr.hit_point = sr.local_hit_point;
			return true;
		}
	}

	return false;
}

bool Sphere::shadow_hit(const Ray& ray, float& tmin) const
{
	if (!shadows)
		return false;
	double t;
	glm::vec3 temp = ray.o - center;
	double a = glm::dot(ray.d, ray.d);
	double b = 2.0f * glm::dot(temp, glm::vec3(ray.d));
	double c = glm::dot(temp, temp) - radius*radius;

	double disc = b*b - 4 * a*c;

	if (disc < 0.0)
		return false;	// 不遮挡光源
	else {
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root

		if (t > kEpsilon) {
			tmin = t;
			return (true);
		}

		t = (-b + e) / denom;    // larger root

		if (t > kEpsilon) {
			tmin = t;
			return (true);
		}
	}

	return false;
}

glm::vec3 Sphere::get_normal(const glm::vec3& point)
{
	glm::vec3 n = point - glm::vec3(center);
	n = glm::normalize(n);

	return n;
}

BBox Sphere::get_bounding_box()
{
	double delta = 0.0001;

	BBox s_box(
		center - glm::dvec3(radius + delta, radius + delta, radius + delta),
		center + glm::dvec3(radius + delta, radius + delta, radius + delta)
	);

	return s_box;
}