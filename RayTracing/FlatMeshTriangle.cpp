#include "Constants.h"
#include "FlatMeshTriangle.h"
#include "ShadeRec.h"

FlatMeshTriangle::FlatMeshTriangle()
	:MeshTriangle()
{}

FlatMeshTriangle::FlatMeshTriangle(Mesh* _mesh_ptr, int i0, int i1, int i2)
	: MeshTriangle(_mesh_ptr, i0, i1, i2)
{

}

FlatMeshTriangle::~FlatMeshTriangle()
{}

bool FlatMeshTriangle::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
{
	glm::vec3 v0(mesh_ptr->vertices[index0]);
	glm::vec3 v1(mesh_ptr->vertices[index1]);
	glm::vec3 v2(mesh_ptr->vertices[index2]);

	double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.d.x, d = v0.x - ray.o.x;
	double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.d.y, h = v0.y - ray.o.y;
	double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.d.z, l = v0.z - ray.o.z;

	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, s = e * j - f * i;

	double inv_denom = 1.0 / (a * m + b * q + c * s);

	double e1 = d * m - b * n - c * p;
	double beta = e1 * inv_denom;

	if (beta < 0.0)
		return (false);

	double r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * inv_denom;

	if (gamma < 0.0)
		return (false);

	if (beta + gamma > 1.0)
		return (false);

	double e3 = a * p - b * r + d * s;
	double t = e3 * inv_denom;

	if (t < kEpsilon)
		return (false);

	tmin = t;
	sr.normal = normal;  	// for flat shading
	sr.local_hit_point = ray.o + t * ray.d;
	sr.hit_point = sr.local_hit_point;

	return (true);
}

void FlatMeshTriangle::compute_normal(bool reverse_normal)
{
	glm::vec3 temp1 = mesh_ptr->vertices[index1] - mesh_ptr->vertices[index0];
	glm::vec3 temp2 = mesh_ptr->vertices[index2] - mesh_ptr->vertices[index0];

	normal = glm::cross(temp1, temp2);
	normal = glm::normalize(normal);

	if (noneed_reverse)
		return;

	if (reverse_normal)
		normal = -normal;
}