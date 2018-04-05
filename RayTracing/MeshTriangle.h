#ifndef __MESH_TRIANGLE_H__
#define __MESH_TRIANGLE_H__

#include "GeometricObject.h"
#include "Mesh.h"

class MeshTriangle :public GeometricObject
{
public:
	Mesh* mesh_ptr;
	int index0, index1, index2;
	glm::vec3 normal;
	float area;

public:
	MeshTriangle();
	MeshTriangle(Mesh* _mesh_ptr, int i1, int i2, int i3);
	virtual ~MeshTriangle();

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const = 0;
	virtual bool shadow_hit(const Ray& ray, float& t) const;
	
	void compute_normal(bool reverse_normal);
	virtual glm::vec3 get_normal() const;
	virtual BBox get_bounding_box();



};

#endif // !__MESH_TRIANGLE_H__
