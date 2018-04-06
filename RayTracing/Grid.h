#ifndef __GRID_H__
#define __GRID_H__

#include "Compound.h"
#include "ShadeRec.h"
#include "Mesh.h"

class Grid :public Compound
{
public:
	Grid();
	Grid(Mesh* _mesh_ptr);
	virtual ~Grid();
	virtual BBox get_bounding_box();

	void read_flat_triangles(char* file_name);
	//void read_smooth_triangles(char* file_name);
	//void tessellate_flat_sphere(const int horizontal_steps, const int vertical_steps);
	//void tessellate_smooth_sphere(const int horizontal_steps, const int vertical_steps);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
	void setup_cells();

	void store_material(Material* material, const int index);
	void set_shared_material_for_all(Material* material);
	//void read_flat_uv_triangles(char* file_name);
	//void read_smooth_uv_triangles(char* file_name);
	//void read_uv_ply_file(char* file_name, const int triangle_type);

private:
	std::vector<GeometricObject*> cells;	// grid of cells, not objects. objects stored in base-class
	std::vector<Material*> store_mtls;
	int nx, ny, nz;		// number of cells
	BBox bbox;			// bounding box ?
	Mesh* mesh_ptr;		// store triangle data
	bool reverse_normal;
	
	glm::vec3 find_min_bounds();
	glm::vec3 find_max_bounds();

	// void read_ply_file(char* file_name, const int triangle_type);
	void read_obj_file(char* file_name, const int triangle_type);
	void compute_mesh_normals();
	
	void construct_material_byhand();

};

inline void 
Grid::store_material(Material* material_ptr, const int index)
{
	objects[index]->set_material(material_ptr);
}



#endif // !__GRID_H__
