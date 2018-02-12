#include "ShadeRec.h"

ShadeRec::ShadeRec(World& wr)
	: hit_an_object(false),
	local_hit_point(),
	normal(),
	color(0,0,0),
	w(wr)

{

}

ShadeRec::ShadeRec()
	:w(World())
{}

ShadeRec::ShadeRec(const ShadeRec& sr)
	:w(sr.w)	// Ӧ�����͵ĳ�ʼ��һ��Ҫ���ڳ�ʼ���б�����ܷ��ڹ��캯���������Ϊʲô��
{
	hit_an_object = sr.hit_an_object;
	local_hit_point = sr.local_hit_point;
	normal = sr.normal;
	color = sr.color;
	
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