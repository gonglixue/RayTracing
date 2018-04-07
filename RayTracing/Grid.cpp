#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <string>
#include <glm/glm.hpp>

#include "Constants.h"
#include "Grid.h"
#include "FlatMeshTriangle.h"

// ?
#include "Triangle.h"

#include "Matte.h"
#include "Emissive.h"
#include "Reflective.h"
#include "Jittered.h"

Grid::Grid()
	:Compound(),
	nx(0),
	ny(0),
	nz(0),
	mesh_ptr(new Mesh),
	reverse_normal(false)
{

}

// constructor, cells is null
Grid::Grid(Mesh* _mesh_ptr)
	:Compound(),
	nx(0),
	ny(0),
	mesh_ptr(_mesh_ptr),
	reverse_normal(false)
{}

Grid::~Grid(){}

BBox Grid::get_bounding_box()
{
	return this->bbox;
}

void Grid::setup_cells()
{
	glm::vec3 p_min = find_min_bounds();
	glm::vec3 p_max = find_max_bounds();

	bbox.x0_ = p_min.x;
	bbox.y0_ = p_min.y;
	bbox.z0_ = p_min.z;

	bbox.x1_ = p_max.x;
	bbox.y1_ = p_max.y;
	bbox.z1_ = p_max.z;

	int num_objects = objects.size();	//?

	double wx = p_max.x - p_min.x;
	double wy = p_max.y - p_min.y;
	double wz = p_max.z - p_min.z;

	// mutiplier scales the number of grid cells relative to the number of objects
	double multiplier = 2.0;

	double s = pow(wx*wy*wz / num_objects, 0.333333);
	nx = multiplier*wx / s + 1;
	ny = multiplier*wy / s + 1;
	nz = multiplier*wz / s + 1;

	int num_cells = nx*ny*nz;
	cells.reserve(num_objects);	//?
	for (int j = 0; j < num_cells; j++)
		cells.push_back(NULL);

	// store the number of objects in each cell
	std::vector<int> counts;
	counts.reserve(num_cells);

	for (int j = 0; j < num_cells; j++)
		counts.push_back(0);

	// put the objects into the cells
	BBox obj_bBox;	// object's bounding box
	int index;		// cell's array index

	for (int j = 0; j < num_objects; j++) {
		obj_bBox = objects[j]->get_bounding_box();	//?

		// compute the cell indices at the corners of the bounding box of the object
		// 最小点所处的栅格坐标
		int ixmin = clamp((obj_bBox.x0_ - p_min.x)*nx / wx, 0, nx - 1);
		int iymin = clamp((obj_bBox.y0_ - p_min.y)*ny / wy, 0, ny - 1);
		int izmin = clamp((obj_bBox.z0_ - p_min.z)*nz / wz, 0, nz - 1);
		// 最大点所处的栅格坐标
		int ixmax = clamp((obj_bBox.x1_ - p_min.x)*nx / wx, 0, nx - 1);
		int iymax = clamp((obj_bBox.y1_ - p_min.y)*ny / wy, 0, ny - 1);
		int izmax = clamp((obj_bBox.z1_ - p_min.z)*nz / wz, 0, nz - 1);

		// add the object to coresponding cells
		// one object can be added to multiple cells
		for (int iz = izmin; iz <= izmax; iz++) {
			for (int iy = iymin; iy <= iymax; iy++) {
				for (int ix = ixmin; ix <= ixmax; ix++) {
					index = ix + nx*iy + nx*ny*iz;
					if (counts[index] == 0) {
						cells[index] = objects[j];
						counts[index] += 1;
					}
					else {
						// 每个cell存储的物体是个Compound
						if (counts[index] == 1) {
							Compound* compound_ptr = new Compound;
							compound_ptr->add_object(cells[index]);
							compound_ptr->add_object(objects[j]);
							cells[index] = compound_ptr;
							counts[index] += 1;
						}
						else {
							cells[index]->add_object(objects[j]);
							counts[index] += 1;
						}
					}
				}
			}
		}
	}// for (int j=0;j<num_objects;j++)

	// debug info
	int num_zeros = 0;		// 空cell个数
	int num_ones = 0;		// 只有1个物体的cell个数
	int num_twos = 0;
	int num_threes = 0;
	int num_greater = 0;
	for (int j = 0; j < num_cells; j++) {
		if (counts[j] == 0)
			num_zeros += 1;
		else if (counts[j] == 1)
			num_ones++;
		else if (counts[j] == 2)
			num_twos++;
		else if (counts[j] == 3)
			num_threes++;
		else
			num_greater += 1;

	}

	std::cout << "finish setup cells\n";
	std::cout << "num_cells: " << num_cells << std::endl;
	std::cout << "num_zeros: " << num_zeros << std::endl;
	std::cout << "num_twos: " << num_twos << std::endl;
	std::cout << "num_threes: " << num_threes << std::endl;
	std::cout << "num_greater: " << num_greater << std::endl;

	// clean count vector
	counts.erase(counts.begin(), counts.end());
}

// find minimum grid point from the boundingbox of all objects
glm::vec3 Grid::find_min_bounds()
{
	BBox object_box;
	glm::vec3 p0(kHugeValue);

	int num_objects = objects.size();
	for (int j = 0; j < num_objects; j++)
	{
		object_box = objects[j]->get_bounding_box();

		if (object_box.x0_ < p0.x)
			p0.x = object_box.x0_;
		if (object_box.y0_ < p0.y)
			p0.y = object_box.y0_;
		if (object_box.z0_ < p0.z)
			p0.z = object_box.z0_;
	}

	p0.x -= kEpsilon;
	p0.y -= kEpsilon;
	p0.z -= kEpsilon;

	return p0;
}

glm::vec3 Grid::find_max_bounds()
{
	BBox object_box;
	glm::vec3 p1(-kHugeValue);

	int num_objects = objects.size();

	for (int j = 0; j < num_objects; j++) {
		object_box = objects[j]->get_bounding_box();

		if (object_box.x1_ > p1.x)
			p1.x = object_box.x1_;
		if (object_box.y1_ > p1.y)
			p1.y = object_box.y1_;
		if (object_box.z1_ > p1.z)
			p1.z = object_box.z1_;
	}

	p1.x += kEpsilon; p1.y += kEpsilon; p1.z += kEpsilon;

	return (p1);
}

void Grid::read_flat_triangles(char* file_name)
{
	read_obj_file(file_name, 0);
}

void Grid::read_obj_file(char* file_name, const int tri_type)
{
	//test
	construct_material_byhand();

	std::ifstream input_file(file_name);
	const int LINE_LENGTH = 100;

	int vert_num = 0, face_num = 0;
	//std::vector<glm::vec3> vertices;
	//std::vector<glm::ivec3> faces;
	mesh_ptr->vertices.clear();

	bool already_normalize = false;
	glm::vec3 max_vert, min_vert;
	max_vert = glm::vec3(-kHugeValue);
	min_vert = glm::vec3(kHugeValue);

	//Compound* component;
	bool begining = true;
	int mtl_state = -1;


	while (input_file) {
		std::string type;
		input_file >> type;	// 读取一词
		switch (type[0]) {
		case '#': {
			char comment[LINE_LENGTH];
			input_file.getline(comment, LINE_LENGTH);
			printf("# %s\n", comment);
			break;
		}
		case 'v': {
			vert_num++;
			float x, y, z;
			input_file >> x >> y >> z;
			// vertices.push_back(glm::vec3(x, y, z));
			mesh_ptr->vertices.push_back(glm::vec3(x, y, z));

			{
				if (x < min_vert.x)
					min_vert.x = x;
				if (x > max_vert.x)
					max_vert.x = x;
				if (y < min_vert.y)
					min_vert.y = y;
				if (y > max_vert.y)
					max_vert.y = y;
				if (z < min_vert.z)
					min_vert.z = z;
				if (z > max_vert.z)
					max_vert.z = z;
			}

			break;
		}
		case 'f': {
			face_num++;
			int i0, i1, i2;
			input_file >> i0 >> i1 >> i2;

			if (tri_type == 0) // FLAT
			{
				FlatMeshTriangle* triangle_ptr = new FlatMeshTriangle(mesh_ptr, i0 - 1, i1 - 1, i2 - 1);
				//triangle_ptr->compute_normal(false);
				triangle_ptr->set_material(store_mtls[mtl_state]);
				objects.push_back(triangle_ptr);
				//component->add_object(triangle_ptr);
				if (mtl_state == 4)
				{
					//printf("set emissive mtl\n");
					triangle_ptr->set_shadows(false);
				}
				if (mtl_state == 3 || mtl_state == 5)
				{
					triangle_ptr->noneed_reverse = true;
				}
				else
					triangle_ptr->noneed_reverse = false;
			}

			break;
		}
		case 'u': {
			mtl_state++;
		}
		default:
			break;
				  
		}
	}
	input_file.close();

	// vertices info
	mesh_ptr->num_vertices = vert_num;
	

	// faces info
	mesh_ptr->num_triangles = face_num;

	mesh_ptr->Normailize_mesh(min_vert, max_vert, 150);
	for (int i = 0; i < objects.size(); i++) {
		dynamic_cast<FlatMeshTriangle*>(objects[i])->compute_normal(true);
	}

	std::cout << "finish reading obj file\n";
	std::cout << "num_vertices: " << mesh_ptr->vertices.size() << std::endl;
	std::cout << "object size: " << this->objects.size() << std::endl;

}

bool Grid::hit(const Ray& ray, double& t, ShadeRec& sr) const
{
	double ox = ray.o.x;
	double oy = ray.o.y;
	double oz = ray.o.z;
	double dx = ray.d.x;
	double dy = ray.d.y;
	double dz = ray.d.z;

	double x0 = bbox.x0_;
	double y0 = bbox.y0_;
	double z0 = bbox.z0_;
	double x1 = bbox.x1_;
	double y1 = bbox.y1_;
	double z1 = bbox.z1_;

	double tx_min, ty_min, tz_min;
	double tx_max, ty_max, tz_max;

	double a = 1.0 / dx;
	if (a >= 0) {
		tx_min = (x0 - ox) * a;
		tx_max = (x1 - ox) * a;
	}
	else {
		tx_min = (x1 - ox) * a;
		tx_max = (x0 - ox) * a;
	}

	double b = 1.0 / dy;
	if (b >= 0) {
		ty_min = (y0 - oy) * b;
		ty_max = (y1 - oy) * b;
	}
	else {
		ty_min = (y1 - oy) * b;
		ty_max = (y0 - oy) * b;
	}

	double c = 1.0 / dz;
	if (c >= 0) {
		tz_min = (z0 - oz) * c;
		tz_max = (z1 - oz) * c;
	}
	else {
		tz_min = (z1 - oz) * c;
		tz_max = (z0 - oz) * c;
	}

	double t0, t1;
	t0 = max(max(tx_min, ty_min), tz_min);
	t1 = min(min(tx_max, ty_max), tz_max);
	if (t0 > t1)
		// 不与grid大包围盒碰撞
		return false;

	int ix, iy, iz;
	if (bbox.inside(ray.o)) {
		// 光线起点的栅格坐标
		ix = clamp((ox - x0) * nx / (x1 - x0), 0, nx - 1);
		iy = clamp((oy - y0) * ny / (y1 - y0), 0, ny - 1);
		iz = clamp((oz - z0) * nz / (z1 - z0), 0, nz - 1);
	}
	else
	{
		// 进入点 p
		glm::vec3 p = ray.o + t0*ray.d;
		// 求碰撞点p的栅格坐标
		ix = clamp((p.x - x0) * nx / (x1 - x0), 0, nx - 1);
		iy = clamp((p.y - y0) * ny / (y1 - y0), 0, ny - 1);
		iz = clamp((p.z - z0) * nz / (z1 - z0), 0, nz - 1);
	}

	// 扫描, 计算穿越的邻接栅格是在x方向上还是y方向上
	// 单位栅格的世界坐标长度
	double dtx = (tx_max - tx_min) / nx;	// （x1 - x0)/nx ?
	double dty = (ty_max - ty_min) / ny;
	double dtz = (tz_max - tz_min) / nz;

	double tx_next, ty_next, tz_next;
	int ix_step, iy_step, iz_step;
	int ix_stop, iy_stop, iz_stop;

	if (dx > 0) {
		tx_next = tx_min + (ix + 1) * dtx;
		ix_step = +1;
		ix_stop = nx;
	}
	else {
		tx_next = tx_min + (nx - ix) * dtx;
		ix_step = -1;
		ix_stop = -1;
	}
	if (dx == 0.0) {
		tx_next = kHugeValue;
		ix_step = -1;
		ix_stop = -1;
	}

	if (dy > 0) {
		ty_next = ty_min + (iy + 1) * dty;
		iy_step = +1;
		iy_stop = ny;
	}
	else {
		ty_next = ty_min + (ny - iy) * dty;
		iy_step = -1;
		iy_stop = -1;
	}
	if (dy == 0.0) {
		ty_next = kHugeValue;
		iy_step = -1;
		iy_stop = -1;
	}

	if (dz > 0) {
		tz_next = tz_min + (iz + 1) * dtz;
		iz_step = +1;
		iz_stop = nz;
	}
	else {
		tz_next = tz_min + (nz - iz) * dtz;
		iz_step = -1;
		iz_stop = -1;
	}
	if (dz == 0.0) {
		tz_next = kHugeValue;
		iz_step = -1;
		iz_stop = -1;
	}

	// traverse the grid
	while (true)
	{
		GeometricObject* object_ptr = cells[ix + nx*iy + nx*ny*iz];	//当前栅格的复合物体

		if (tx_next < ty_next && tx_next < tz_next) {	// 下个栅格是x方向的
			if (object_ptr && object_ptr->hit(ray, t, sr) && t < tx_next) {
				material_ptr = object_ptr->get_material();
				return true;
			}

			tx_next += dtx;
			ix += ix_step;
			if (ix == ix_stop)
				return false;
		}
		else {
			if (ty_next < tz_next)		// 下个栅格是y方向的
			{
				if (object_ptr && object_ptr->hit(ray, t, sr) && t < ty_next) {
					material_ptr = object_ptr->get_material();
					return (true);
				}

				ty_next += dty;
				iy += iy_step;

				if (iy == iy_stop)
					return (false);
			}
			else {
				// 下个栅格是z方向的
				if (object_ptr && object_ptr->hit(ray, t, sr) && t < tz_next) {
					material_ptr = object_ptr->get_material();
					return (true);
				}

				tz_next += dtz;
				iz += iz_step;

				if (iz == iz_stop)
					return (false);
			}
		}
	}

} // end of hit

// 计算顶点平均法向量
void Grid::compute_mesh_normals()
{
	mesh_ptr->normals.clear();
	mesh_ptr->normals.reserve(mesh_ptr->num_vertices);
	// TODO
}

void Grid::set_shared_material_for_all(Material* mat)
{
	std::cout << "set shared material for all objects in grid.\n";

	int num_obj = get_num_objects();
	for (int i = 0; i < num_obj; i++)
	{
		objects[i]->set_material(mat);
	}
}

void Grid::construct_material_byhand()
{
	Jittered* sampler_ptr = new Jittered(16);

	Matte* matte_floor = new Matte;
	matte_floor->set_cd(1.0);
	matte_floor->set_ka(0);
	matte_floor->set_kd(0.5);
	matte_floor->set_sampler(sampler_ptr);
	matte_floor->mat_name = "floor";
	store_mtls.push_back(matte_floor);

	Matte* matte_blue_wall = new Matte;
	matte_blue_wall->set_cd(0, 0, 1.0);
	matte_blue_wall->set_ka(0);
	matte_blue_wall->set_kd(1.0);
	matte_blue_wall->set_sampler(sampler_ptr);
	matte_blue_wall->mat_name = "blue";
	store_mtls.push_back(matte_blue_wall);

	Matte* matte_red_wall = new Matte;
	matte_red_wall->set_cd(1.0, 0, 0);
	matte_red_wall->set_ka(0);
	matte_red_wall->set_kd(1.0);
	matte_red_wall->set_sampler(sampler_ptr);
	matte_red_wall->mat_name = "red";
	store_mtls.push_back(matte_red_wall);

	Reflective* reflective_ptr1 = new Reflective;
	reflective_ptr1->set_ka(0);	// 环境光系数
	reflective_ptr1->set_kd(0.5);	// 漫反射系数
	reflective_ptr1->set_cd(0.5, 0.5, 0.5);	// yellow
	reflective_ptr1->set_ks(0.15);			// phong模型的specular系数
	reflective_ptr1->set_exp(100.0);
	reflective_ptr1->set_kr(0.75);
	reflective_ptr1->set_color(WHITE);
	reflective_ptr1->mat_name = "reflect";
	store_mtls.push_back(reflective_ptr1);

	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->set_color(WHITE);
	emissive_ptr->set_radiance(1.5);
	emissive_ptr->mat_name = "light";
	store_mtls.push_back(emissive_ptr);

	Matte* transparent_sphere = new Matte;
	transparent_sphere->set_cd(1.0);
	transparent_sphere->set_ka(0);
	transparent_sphere->set_kd(1.0);
	transparent_sphere->set_sampler(sampler_ptr);
	transparent_sphere->mat_name = "transparent";
	store_mtls.push_back(transparent_sphere);
}