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
		int ixmin = clamp((obj_bBox.x0_ - p_min.x)*nx / wx, 0, nx - 1);
		int iymin = clamp((obj_bBox.y0_ - p_min.y)*ny / wy, 0, ny - 1);
		int izmin = clamp((obj_bBox.z0_ - p_min.z)*nz / wz, 0, nz - 1);

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
	std::ifstream input_file(file_name);
	const int LINE_LENGTH = 100;

	int vert_num = 0, face_num = 0;

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
			// TODO

			break;
		}
		case 'f': {
			face_num++;
			int i0, i1, i2;
			input_file >> i0 >> i1 >> i2;
			// TODO

			break;
		}
		default:
			break;
				  
		}
	}
}