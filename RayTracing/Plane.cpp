#include "Plane.h"
#include "ShadeRec.h"
//const double Plane::kEpsilon = 0.001;	// static const���͵ĳ�ʼ��

Plane::Plane()
	:GeometricObject(),
	point(0.0),
	normal(0, 1, 0)
{}

Plane::Plane(const glm::dvec3 _point, const glm::dvec3 _normal)
	: GeometricObject(),
	point(_point),
	normal(_normal)
{
	normal = glm::normalize(normal);
}

// ������Ŀ������캯���������˻���Ŀ������캯��
Plane::Plane(const Plane& plane)
	:GeometricObject(plane),
	point(plane.point),
	normal(plane.normal)
{

}

Plane::~Plane()
{}

Plane& Plane::operator= (const Plane& rhs)
{
	if (this == &rhs)
		return (*this);

	GeometricObject::operator=(rhs);

	point = rhs.point;
	normal = rhs.normal;

	return (*this);
}

// tmin: �����ײ��Ĺ��߲����������践�صĲ�����ShadeRec��������
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