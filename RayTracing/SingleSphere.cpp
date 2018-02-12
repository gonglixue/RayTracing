#include "SingleSphere.h"
#include "World.h"
#include "ShadeRec.h"

SingleSphere::SingleSphere()
	:Tracer()
{}

SingleSphere::SingleSphere(World* _world_ptr)
	:Tracer(_world_ptr)
{}

// 派生类的析构函数能否显示调用基类的构造函数？还是会自动地调用？
SingleSphere::~SingleSphere()
{}

glm::vec3 SingleSphere::trace_ray(const Ray& ray) const
{
	ShadeRec sr(*world_ptr);
	double t;

	if (world_ptr->sphere.hit(ray, t, sr))
		return RED;
	else
		return BLACK;
}