#include "Plane.h"
#include "ShadeRec.h"
//const double Plane::kEpsilon = 0.001;	// static const类型的初始化

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

// 派生类的拷贝构造函数，调用了基类的拷贝构造函数
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

// tmin: 最近碰撞点的光线参数，其他需返回的参数由ShadeRec变量带回
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