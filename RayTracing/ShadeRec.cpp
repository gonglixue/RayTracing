#include "ShadeRec.h"
#include "Material.h"

ShadeRec::ShadeRec(World& wr)
	: hit_an_object(false),
	local_hit_point(),
	normal(),
	color(0,0,0),
	w(wr),
	material_ptr(NULL),
	hit_point(),
	ray(),
	depth(0)
	//dir()
{

}

ShadeRec::ShadeRec()
	:w(World())
{}

ShadeRec::ShadeRec(const ShadeRec& sr)
	:w(sr.w)	// 引用类型的初始化一定要放在初始化列表里，不能放在构造函数体里，这是为什么？
{
	hit_an_object = sr.hit_an_object;
	material_ptr = sr.material_ptr;
	hit_point = sr.hit_point;
	local_hit_point = sr.local_hit_point;
	normal = sr.normal;
	color = sr.color;
	
	ray = sr.ray;
	depth = sr.depth;
	t = 0.0;
	u = v = 0.0;
	// dir = sr.dir;
}



ShadeRec& ShadeRec:: operator= (const ShadeRec& rhs)
{
	if (this == &rhs)
		return (*this);

	hit_an_object = rhs.hit_an_object;
	local_hit_point = rhs.local_hit_point;
	normal = rhs.normal;
	color = rhs.color;
	w = rhs.w;

	return (*this);
}