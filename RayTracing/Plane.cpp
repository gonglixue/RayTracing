#include "Plane.h"

// tmin: �����ײ��Ĺ��߲���
bool Plane::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
{
	//double t = (point - ray.o) * normal / (ray.d * normal);
	double t = glm::dot(point - ray.o, normal) / glm::dot(ray.d, normal);

	if (t > kEpsilon)
	{
		tmin = t;
		sr.normal = normal;
		sr.local_hit_point = ray.o + t * ray.d;

		return true;
	}
	else
		return false;
}