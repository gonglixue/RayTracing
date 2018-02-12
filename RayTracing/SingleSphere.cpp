#include "SingleSphere.h"
#include "World.h"
#include "ShadeRec.h"

SingleSphere::SingleSphere()
	:Tracer()
{}

SingleSphere::SingleSphere(World* _world_ptr)
	:Tracer(_world_ptr)
{}

// ����������������ܷ���ʾ���û���Ĺ��캯�������ǻ��Զ��ص��ã�
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