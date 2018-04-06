#ifndef __FLAT_MESH_TRIANGLE_H__
#define __FLAT_MESH_TRIANGLE_H__

#include "MeshTriangle.h"
class FlatMeshTriangle :public MeshTriangle
{
public:
	FlatMeshTriangle();
	FlatMeshTriangle(Mesh* _mesh_ptr, int i0, int i1, int i2);
	virtual ~FlatMeshTriangle();

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
};
#endif // !__FLAT_MESH_TRIANGLE_H__
