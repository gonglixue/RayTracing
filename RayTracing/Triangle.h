#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "GeometricObject.h"

class Triangle :public GeometricObject
{
public:
	Triangle();
	Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3);
	Triangle(const Triangle& triangle);
	~Triangle();
	Triangle& operator= (const Triangle& rhs);

	virtual BBox get_bounding_box();
	
	void compute_normal();

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
	virtual bool shadow_hit(const Ray& ray, double& tmin) const;	// 该三角形是否遮挡的光线ray

private:
	glm::vec3 v0, v1, v2;
	glm::vec3 normal;
};

#endif // !__TRIANGLE_H__
