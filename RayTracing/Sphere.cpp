#include "Sphere.h"

bool Sphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
{
	double t;
	glm::dvec3 temp = ray.o - center;
	double a = glm::dot(ray.d, ray.d);
	double b = 2.0 * glm::dot(temp, ray.d);
	double c = glm::dot(temp, temp) - radius * radius;
	double disc = b*b - 4 * a*c;

	if (disc < 0.0)
		return false;
	else {
		double e = sqrt(disc);
		double denom = 2 * a;
		t = (-b - e) / denom;  // smaller root

		if (t > kEpsilon) {
			tmin = t;
			sr.normal = (temp + t*ray.d) / (double)radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return true;
		}

		// larger root
		t = (-b + e) / denom;
		if (t > kEpsilon)
		{
			tmin = t;
			sr.normal = (temp + t*ray.d) / (double)radius;
			sr.local_hit_point = ray.o + t*ray.d;
			return true;
		}
	}

	return false;
}