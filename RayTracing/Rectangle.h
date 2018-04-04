#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include "GeometricObject.h"

class Rectangle :public GeometricObject
{
public:
	Rectangle();
	Rectangle(const glm::vec3& _p0, const glm::vec3& _a, const glm::vec3& _b);
	Rectangle(const glm::vec3& _p0, const glm::vec3& _a, const glm::vec3& _b, const glm::vec3& n);
	Rectangle(const Rectangle& r);
	virtual ~Rectangle();
	Rectangle& operator= (const Rectangle& rhs);

	BBox get_bounding_box(void);
	
	virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const;

	// these are used when rectangle is an arean light
	virtual void set_sampler(Sampler* sampler);
	virtual glm::vec3 sample();
	virtual glm::vec3 get_normal(const glm::vec3& p);
	virtual float pdf(const ShadeRec& sr);

private:
	glm::vec3 p0;		// conner verex
	glm::vec3 a;		// side
	glm::vec3 b;		// side
	double a_len_squared;		// square of the length of side a
	double b_len_squared;		// square of the length of side b
	glm::vec3 normal;
	
	// following are used when rectangle is an area light
	float area;
	float inv_area;
	Sampler* sampler_ptr;




};
#endif // !__RECTANGLE_H__
