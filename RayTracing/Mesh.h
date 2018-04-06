#ifndef __MESH_H__
#define __MESH_H__

#include <vector>
#include <glm/glm.hpp>

class Mesh
{
public:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<float> u;		// used for texture
	std::vector<float> v;

	//std::vector<std::vector<int>> vertex_faces;	// triangles shared by each vertex

	int num_vertices;
	int num_triangles;

	Mesh();
	Mesh(const Mesh& mesh);
	~Mesh();
	Mesh& operator= (const Mesh& rhs);

	void Normailize_mesh(glm::vec3 min, glm::vec3 max, float length=200, glm::vec3 center=glm::vec3(0));
};
#endif // !__MESH_H__
