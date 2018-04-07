#include "ConcaveSphere.h"
#include "ShadeRec.h"

ConcaveSphere::ConcaveSphere()
	:Sphere()
{}

bool ConcaveSphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
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
			sr.normal = -1.0f * glm::normalize(sr.normal);
			sr.local_hit_point = ray.o + t * ray.d;
			sr.hit_point = sr.local_hit_point;			// Lg: treat hit_point as local_hit_point;
			
			printf("hit concave sphere\n");
			return true;
		}

		// larger root
		t = (-b + e) / denom;
		if (t > kEpsilon)
		{
			tmin = t;
			sr.normal = (temp + t*ray.d) / (double)radius;
			sr.normal = -1.0f * glm::normalize(sr.normal);
			sr.local_hit_point = ray.o + t*ray.d;
			sr.hit_point = sr.local_hit_point;

			printf("hit concave sphere\n");
			return true;
		}
	}

	return false;
}