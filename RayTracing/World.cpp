#include "World.h"
#include "SingleSphere.h"
#include "MultipleObjects.h"
#include "ShadeRec.h"
#include "Plane.h"
#include "Maths.h"
#include "Jittered.h"
#include "Ambient.h"
#include "RayCast.h"
#include "PointLight.h"
#include "Directional.h"
#include "Matte.h"
#include "Phong.h"
#include "Emissive.h"
#include "AreaLight.h"
#include "Rectangle.h"
#include "Box.h"
#include "Grid.h"
#include "Reflective.h"
#include "Whitted.h"
#include "PathTrace.h"
#include "ConcaveSphere.h"

World::World()
	:background_color(BLACK),
	frame_buffer(NULL),
	tracer_ptr(NULL),
	camera_ptr(NULL),
	ambient_ptr(new Ambient)
{}

World::~World()
{}

/*
// buil ch22 with grid
void World::build(const int width, const int height)
{
	printf("begin build...\n");
	int num_samples = 1;
	vp.set_hres(width);
	vp.set_vres(height);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);
	vp.set_sampler(new Jittered(num_samples));

	frame_buffer = (GLubyte*)malloc(vp.hres*vp.vres * 3 * sizeof(GLubyte));
	background_color = BLACK;
	tracer_ptr = new RayCast(this);

	// camera
	Pinhole* pinhole = new Pinhole;
	pinhole->set_eye(0, 0, 40);
	pinhole->set_lookat(0, 0, 0);
	pinhole->set_view_distance(100);//到视平面距离
	pinhole->compute_uvw();
	this->set_camera(pinhole);

	// TODO
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(-10, 20, 20);
	light_ptr->scale_radiance(3.0);
	light_ptr->set_shadows(false);
	add_light(light_ptr);

	int num_sphere = 100;
	float volume = 0.1 / num_sphere;
	float radius = 10.0f * pow(0.75 * volume / PI, 0.333);

	Grid* grid_ptr = new Grid;
	set_rand_seed(15);

	for (int j = 0; j < num_sphere; j++)
	{
		Matte* matte_ptr = new Matte;
		matte_ptr->set_ka(0.25);
		matte_ptr->set_kd(0.75);
		matte_ptr->set_cd(rand_float(), rand_float(), rand_float());

		Sphere* sphere_ptr = new Sphere;
		sphere_ptr->set_radius(radius);
		sphere_ptr->set_center(10 - 20*rand_float(), 10 - 20*rand_float(), 10 - 20*rand_float());
		sphere_ptr->set_material(matte_ptr);
		grid_ptr->add_object(sphere_ptr);
	}
	grid_ptr->setup_cells();

	add_object(grid_ptr);
	open_window(width, height);


}
*/

/*
void World::build(const int width, const int height)
{
	printf("begin build...\n");
	int num_samples = 16;
	vp.set_hres(width);
	vp.set_vres(height);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);
	vp.set_sampler(new Jittered(num_samples));

	frame_buffer = (GLubyte*)malloc(vp.hres*vp.vres * 3 * sizeof(GLubyte));
	background_color = BLACK;
	tracer_ptr = new RayCast(this);

	// camera
	Pinhole* pinhole = new Pinhole;
	pinhole->set_eye(-20, 10, 50);
	pinhole->set_lookat(0, 2, 0);
	pinhole->set_view_distance(1080);//到视平面距离
	pinhole->compute_uvw();
	this->set_camera(pinhole);

	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->set_radiance(40.0);
	emissive_ptr->set_color(1.0, 1.0, 1.0);

	// define rectangle
	float rec_width = 4.0;
	float rec_height = 4.0;
	glm::vec3 center(0.0, 7.0, -7.0);	// center of area light
	glm::vec3 p0(-0.5 * rec_width, center.y - 0.5 * rec_height, center.z);
	glm::vec3 a(rec_width, 0, 0);
	glm::vec3 b(0, rec_height, 0);
	glm::vec3 normal(0, 0, 1);

	Rectangle* rectangle_ptr = new Rectangle(p0, a, b, normal);
	rectangle_ptr->set_material(emissive_ptr);
	rectangle_ptr->set_sampler(new Jittered(num_samples));
	rectangle_ptr->set_shadows(false);
	add_object(rectangle_ptr);

	// arealight
	AreaLight* area_light_ptr = new AreaLight;
	area_light_ptr->set_object(rectangle_ptr);
	area_light_ptr->set_shadows(true);
	add_light(area_light_ptr);

	// Four axis aligned boxes

	float box_width = 1.0; 		// x dimension
	float box_depth = 1.0; 		// z dimension
	float box_height = 4.5; 		// y dimension
	float gap = 3.0;

	Matte* matte_ptr1 = new Matte;
	matte_ptr1->set_ka(0.25);
	matte_ptr1->set_kd(0.75);
	matte_ptr1->set_cd(0.4, 0.7, 0.4);     // green

	Box* box_ptr0 = new Box(glm::vec3(-1.5 * gap - 2.0 * box_width, 0.0, -0.5 * box_depth),
		glm::vec3(-1.5 * gap - box_width, box_height, 0.5 * box_depth));
	box_ptr0->set_material(matte_ptr1);
	add_object(box_ptr0);

	Box* box_ptr1 = new Box(glm::vec3(-0.5 * gap - box_width, 0.0, -0.5 * box_depth),
		glm::vec3(-0.5 * gap, box_height, 0.5 * box_depth));
	box_ptr1->set_material(matte_ptr1);
	add_object(box_ptr1);

	Box* box_ptr2 = new Box(glm::vec3(0.5 * gap, 0.0, -0.5 * box_depth),
		glm::vec3(0.5 * gap + box_width, box_height, 0.5 * box_depth));
	box_ptr2->set_material(matte_ptr1);
	add_object(box_ptr2);

	Box* box_ptr3 = new Box(glm::vec3(1.5 * gap + box_width, 0.0, -0.5 * box_depth),
		glm::vec3(1.5 * gap + 2.0 * box_width, box_height, 0.5 * box_depth));
	box_ptr3->set_material(matte_ptr1);
	add_object(box_ptr3);

	// floor plane
	Matte* matte_ptr2 = new Matte;
	matte_ptr2->set_ka(0.1);
	matte_ptr2->set_kd(0.90);
	matte_ptr2->set_cd(1.0);

	Plane* plane_ptr = new Plane(glm::vec3(0.0), glm::vec3(0, 1, 0));
	plane_ptr->set_material(matte_ptr2);
	add_object(plane_ptr);

	open_window(width, height);
}
*/

/* 去掉area light是正确的
=======
	// camera
	Pinhole* pinhole = new Pinhole;
	pinhole->set_eye(-20, 10, 50);
	pinhole->set_lookat(0, 2, 0);
	pinhole->set_view_distance(1080);//到视平面距离
	pinhole->compute_uvw();
	this->set_camera(pinhole);

	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->set_radiance(40.0);
	emissive_ptr->set_color(1.0, 1.0, 1.0);

	// define rectangle
	float rec_width = 4.0;
	float rec_height = 4.0;
	glm::vec3 center(0.0, 7.0, -7.0);	// center of area light
	glm::vec3 p0(-0.5 * rec_width, center.y - 0.5 * rec_height, center.z);
	glm::vec3 a(rec_width, 0, 0);
	glm::vec3 b(0, rec_height, 0);
	glm::vec3 normal(0, 0, 1);

	Rectangle* rectangle_ptr = new Rectangle(p0, a, b, normal);
	rectangle_ptr->set_material(emissive_ptr);
	rectangle_ptr->set_sampler(new Jittered(num_samples));
	rectangle_ptr->set_shadows(false);
	add_object(rectangle_ptr);

	// arealight
	AreaLight* area_light_ptr = new AreaLight;
	area_light_ptr->set_object(rectangle_ptr);
	area_light_ptr->set_shadows(true);
	add_light(area_light_ptr);

	// Four axis aligned boxes

	float box_width = 1.0; 		// x dimension
	float box_depth = 1.0; 		// z dimension
	float box_height = 4.5; 		// y dimension
	float gap = 3.0;

	Matte* matte_ptr1 = new Matte;
	matte_ptr1->set_ka(0.25);
	matte_ptr1->set_kd(0.75);
	matte_ptr1->set_cd(0.4, 0.7, 0.4);     // green

	Box* box_ptr0 = new Box(glm::vec3(-1.5 * gap - 2.0 * box_width, 0.0, -0.5 * box_depth),
		glm::vec3(-1.5 * gap - box_width, box_height, 0.5 * box_depth));
	box_ptr0->set_material(matte_ptr1);
	add_object(box_ptr0);

	Box* box_ptr1 = new Box(glm::vec3(-0.5 * gap - box_width, 0.0, -0.5 * box_depth),
		glm::vec3(-0.5 * gap, box_height, 0.5 * box_depth));
	box_ptr1->set_material(matte_ptr1);
	add_object(box_ptr1);

	Box* box_ptr2 = new Box(glm::vec3(0.5 * gap, 0.0, -0.5 * box_depth),
		glm::vec3(0.5 * gap + box_width, box_height, 0.5 * box_depth));
	box_ptr2->set_material(matte_ptr1);
	add_object(box_ptr2);

	Box* box_ptr3 = new Box(glm::vec3(1.5 * gap + box_width, 0.0, -0.5 * box_depth),
		glm::vec3(1.5 * gap + 2.0 * box_width, box_height, 0.5 * box_depth));
	box_ptr3->set_material(matte_ptr1);
	add_object(box_ptr3);

	// floor plane
	Matte* matte_ptr2 = new Matte;
	matte_ptr2->set_ka(0.1);
	matte_ptr2->set_kd(0.90);
	matte_ptr2->set_cd(1.0);

	Plane* plane_ptr = new Plane(glm::vec3(0.0), glm::vec3(0, 1, 0));
	plane_ptr->set_material(matte_ptr2);
	add_object(plane_ptr);

	open_window(width, height);
}*/

/*
// build from obj
void World::build(const int width, const int height)
{
	printf("begin build...\n");
	int num_samples = 16;
	vp.set_hres(width);
	vp.set_vres(height);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);
	vp.set_sampler(new Jittered(num_samples));

	frame_buffer = (GLubyte*)malloc(vp.hres*vp.vres * 3 * sizeof(GLubyte));
	background_color = BLACK;
	tracer_ptr = new RayCast(this);

	//环境光
	Ambient* _ambient_ptr = new Ambient;
	_ambient_ptr->scale_radiance(1.0);
	this->ambient_ptr = _ambient_ptr;

	// camera
	Pinhole* pinhole = new Pinhole;
	pinhole->set_eye(0, 100, 850);
	pinhole->set_lookat(0, 100, 0);
	pinhole->set_view_distance(850.0);//到视平面距离
	pinhole->compute_uvw();
	this->set_camera(pinhole);

	// 光源
	PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(200, 200, 200);
	light_ptr2->scale_radiance(3.0);		//?
	light_ptr2->set_shadows(true);
	this->add_light(light_ptr2);

	Matte* matte_ptr = new Matte;
	matte_ptr->set_ka(0.25);
	matte_ptr->set_kd(0.75);
	matte_ptr->set_cd(rand_float(), rand_float(), rand_float());

	Grid* grid_ptr = new Grid;
	grid_ptr->read_flat_triangles("../scene/scene_01_fix.scene");
	grid_ptr->set_shared_material_for_all(matte_ptr);
	grid_ptr->setup_cells();
	
	add_object(grid_ptr);

	open_window(width, height);

}*/


/*
 //without area light
void World::build(const int width, const int height)
{
	printf("begin build...\n");
	int num_samples = 25;
	vp.set_hres(width);
	vp.set_vres(height);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);
	// vp.set_num_samples(16);
	vp.set_sampler(new Jittered(num_samples));

	frame_buffer = (GLubyte*)malloc(vp.hres*vp.vres * 3 * sizeof(GLubyte));
	background_color = BLACK;
	//tracer_ptr = new SingleSphere(this);
	//tracer_ptr = new MultipleObjects(this);
	// tracer_ptr = new RayCast(this);
	tracer_ptr = new Whitted(this);

	//环境光
	Ambient* _ambient_ptr = new Ambient;
	_ambient_ptr->scale_radiance(0.5);
	this->ambient_ptr = _ambient_ptr;

	// camera
	Pinhole* pinhole = new Pinhole;
	pinhole->set_eye(0, 0, 850);
	pinhole->set_lookat(-5, 0, 0);
	pinhole->set_view_distance(850.0);//到视平面距离
	pinhole->compute_uvw();
	this->set_camera(pinhole);

	// 光源
	PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(-100, 50, -10);
	light_ptr2->scale_radiance(3.0);		//?
	light_ptr2->set_shadows(true);
	this->add_light(light_ptr2);

	// 方向光
	Directional* light_ptr3 = new Directional;
	light_ptr3->set_direction(20, 0, -20);
	light_ptr3->scale_radiance(3.0);
	light_ptr3->set_shadows(true);
	add_light(light_ptr3);

	//自发光
	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->set_radiance(40.0);
	emissive_ptr->set_color(1.0, 1.0, 1.0);


	// objects
	Reflective* reflective_ptr1 = new Reflective;
	reflective_ptr1->set_ka(0.25);	// 环境光系数
	reflective_ptr1->set_kd(0.5);	// 漫反射稀疏
	reflective_ptr1->set_cd(0.75, 0.75, 0);	// yellow
	reflective_ptr1->set_ks(0.15);			// phong模型的specular系数
	reflective_ptr1->set_exp(100.0);
	reflective_ptr1->set_kr(0.75);
	reflective_ptr1->set_color(WHITE);

	Matte* matte_ptr1 = new Matte;
	matte_ptr1->set_ka(0.25);		// 环境光反射系数
	matte_ptr1->set_kd(0.65);		// 漫反射系数
	matte_ptr1->set_cd(1, 1, 0);	// 颜色 黄
	Sphere* sphere_ptr1 = new Sphere(glm::vec3(10, -5, 0), 30);
	sphere_ptr1->set_material(matte_ptr1);
	//sphere_ptr1->set_material(reflective_ptr1);
	sphere_ptr1->object_id = 0;
	this->add_object(sphere_ptr1);

	Matte* matte_ptr2 = new Matte;
	matte_ptr2->set_ka(0.15);
	matte_ptr2->set_kd(0.85);
	matte_ptr2->set_cd(0.71, 0.40, 0.16);   		// brown
	Sphere* sphere_ptr2 = new Sphere(glm::vec3(-25, 10, -35), 30);
	sphere_ptr2->set_material(matte_ptr2);
	sphere_ptr2->set_shadows(false);
	sphere_ptr2->set_sampler(new Jittered(20));
	sphere_ptr2->object_id = 1;
	this->add_object(sphere_ptr2);

	Matte* matte_ptr3 = new Matte;
	matte_ptr3->set_ka(0.15);
	matte_ptr3->set_kd(0.8);
	matte_ptr3->set_cd(0, 0.4, 0.2);				// dark green
	Plane* plane_ptr = new Plane(glm::vec3(0, -35, 0), glm::normalize(glm::vec3(0, 1, 0)));
	// plane_ptr->set_material(matte_ptr3);
	plane_ptr->set_material(reflective_ptr1);
	plane_ptr->object_id = 2;
	this->add_object(plane_ptr);

	Phong* phong_ptr = new Phong;
	phong_ptr->set_ka(0.25);
	phong_ptr->set_kd(0.6);
	phong_ptr->set_cd(0.5);
	phong_ptr->set_ks(0.2);
	phong_ptr->set_exp(20);
	Sphere* sphere_ptr3 = new Sphere(glm::vec3(-50, 0, -10), 30);
	sphere_ptr3->set_material(phong_ptr);
	sphere_ptr3->object_id = 3;
	this->add_object(sphere_ptr3);

	//AreaLight* area_light_ptr = new AreaLight;
	//area_light_ptr->set_object(sphere_ptr2);
	//area_light_ptr->set_shadows(true);
	//add_light(area_light_ptr);

	open_window(width, height);
}
*/

/* without material
void World::build(const int width, const int height)
{
	printf("begin build...\n");
	int num_samples = 25;
	vp.set_hres(width);
	vp.set_vres(height);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);
	// vp.set_num_samples(16);
	vp.set_sampler(new Jittered(num_samples));

	frame_buffer = (GLubyte*)malloc(vp.hres*vp.vres * 3 * sizeof(GLubyte));
	background_color = BLACK;
	//tracer_ptr = new SingleSphere(this);
	tracer_ptr = new MultipleObjects(this);

	// camera
	Pinhole* pinhole = new Pinhole;
	pinhole->compute_uvw();
	this->set_camera(pinhole);

	//sphere_.set_center(0.0, 0.0, 0.0);
	//sphere_.set_radius(85.0);
	// world objects
	Sphere* sphere_ptr = new Sphere;
	sphere_ptr->set_center(0, -25, 0);
	sphere_ptr->set_radius(80.0);
	sphere_ptr->set_color(1, 0, 0);
	add_object(sphere_ptr);

	sphere_ptr = new Sphere(glm::dvec3(0, 20, 0), 60);
	sphere_ptr->set_color(1, 1, 0); //yellow
	add_object(sphere_ptr);

	Plane* plane_ptr = new Plane(glm::dvec3(0), glm::dvec3(0, 1, 1));
	plane_ptr->set_color(0, 0.35, 0);//dark green
	add_object(plane_ptr);

	open_window(width, height);
}
*/

 // path trace
/*
void World::build(const int width, const int height)
{
	printf("begin build...\n");
	int num_samples = 25;
	vp.set_hres(width);
	vp.set_vres(height);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);
	// vp.set_num_samples(16);
	vp.set_sampler(new Jittered(num_samples));

	frame_buffer = (GLubyte*)malloc(vp.hres*vp.vres * 3 * sizeof(GLubyte));
	background_color = BLACK;
	tracer_ptr = new PathTrace(this);
	//tracer_ptr = new RayCast(this);

	//环境光
	Ambient* _ambient_ptr = new Ambient;
	_ambient_ptr->scale_radiance(0.0);
	this->ambient_ptr = _ambient_ptr;

	// camera
	Pinhole* pinhole = new Pinhole;
	pinhole->set_eye(70, 20, 70);
	pinhole->set_lookat(-50, 20, -24);
	pinhole->set_view_distance(100);//到视平面距离
	pinhole->compute_uvw();
	this->set_camera(pinhole);

	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->set_color(WHITE);
	emissive_ptr->set_radiance(1.5);
	ConcaveSphere* sphere_ptr = new ConcaveSphere;
	sphere_ptr->set_radius(10000.0);
	sphere_ptr->set_shadows(false);
	sphere_ptr->set_material(emissive_ptr);
	add_object(sphere_ptr);

	float ka = 0.2;
	Matte* matte_ptr1 = new Matte;
	matte_ptr1->set_ka(ka);
	matte_ptr1->set_kd(0.6);
	matte_ptr1->set_cd(WHITE);
	matte_ptr1->set_sampler(new Jittered(num_samples));

	Sphere* sphere_ptr1 = new Sphere(glm::vec3(28, 20, -24), 20);
	sphere_ptr1->set_material(matte_ptr1);
	add_object(sphere_ptr1);

	// small sphere
	Matte* matte_ptr2 = new Matte;
	matte_ptr2->set_ka(ka);
	matte_ptr2->set_kd(0.5);
	matte_ptr2->set_cd(0.85);				// gray
	matte_ptr2->set_sampler(new Jittered(num_samples));

	Sphere* sphere_ptr2 = new Sphere(glm::vec3(34, 12, 13), 12);
	sphere_ptr2->set_material(matte_ptr2);
	add_object(sphere_ptr2);

	// medium sphere
	Matte* matte_ptr3 = new Matte;
	matte_ptr3->set_ka(ka);
	matte_ptr3->set_kd(0.75);
	matte_ptr3->set_cd(0.73, 0.22, 0.0);    // orange
	matte_ptr3->set_sampler(new Jittered(num_samples));

	Sphere* sphere_ptr3 = new Sphere(glm::vec3(-7, 15, 42), 16);
	sphere_ptr3->set_material(matte_ptr3);
	add_object(sphere_ptr3);

	// box
	Matte* matte_ptr5 = new Matte;
	matte_ptr5->set_ka(ka);
	matte_ptr5->set_kd(0.75);
	matte_ptr5->set_cd(0.95);				// gray
	matte_ptr5->set_sampler(new Jittered(num_samples));

	Box* box_ptr = new Box(glm::vec3(-55, 0, -110), glm::vec3(-25, 60, 65));  // thicker
	box_ptr->set_material(matte_ptr5);
	add_object(box_ptr);

	// ground plane
	Reflective* reflective_ptr1 = new Reflective;
	reflective_ptr1->set_ka(0.25);	// 环境光系数
	reflective_ptr1->set_kd(0.5);	// 漫反射稀疏
	reflective_ptr1->set_cd(0.75, 0.75, 0);	// yellow
	reflective_ptr1->set_ks(0.15);			// phong模型的specular系数
	reflective_ptr1->set_exp(100.0);
	reflective_ptr1->set_kr(0.75);
	reflective_ptr1->set_color(WHITE);

	Matte* matte_ptr6 = new Matte;
	matte_ptr6->set_ka(0.15);
	matte_ptr6->set_kd(0.95);
	matte_ptr6->set_cd(0.37, 0.43, 0.08);     // olive green
	matte_ptr6->set_sampler(new Jittered(num_samples));

	Plane* plane_ptr = new Plane(glm::vec3(0, 0.01, 0), glm::vec3(0, 1, 0));
	plane_ptr->set_material(reflective_ptr1);
	add_object(plane_ptr);

	open_window(width, height);
}
*/

// cornell box path tracer
void World::build(const int width, const int height)
{
	printf("begin build...\n");
	int num_samples = 4;
	vp.set_hres(width);
	vp.set_vres(height);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);
	// vp.set_num_samples(16);
	vp.set_sampler(new Jittered(num_samples));

	frame_buffer = (GLubyte*)malloc(vp.hres*vp.vres * 3 * sizeof(GLubyte));
	background_color = BLACK;
	tracer_ptr = new PathTrace(this);
	//tracer_ptr = new RayCast(this);

	//环境光
	Ambient* _ambient_ptr = new Ambient;
	_ambient_ptr->scale_radiance(0.0);
	this->ambient_ptr = _ambient_ptr;

	// camera
	Pinhole* pinhole = new Pinhole;
	pinhole->set_eye(0, 60, 200);
	pinhole->set_lookat(0, 60, 0);
	pinhole->set_view_distance(200.0);//到视平面距离
	pinhole->compute_uvw();
	this->set_camera(pinhole);

	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->set_color(WHITE);
	emissive_ptr->set_radiance(1.5);
	ConcaveSphere* sphere_ptr = new ConcaveSphere;
	sphere_ptr->set_radius(10000.0);
	sphere_ptr->set_shadows(false);
	sphere_ptr->set_material(emissive_ptr);
	add_object(sphere_ptr);

	Grid* grid_ptr = new Grid;
	grid_ptr->read_flat_triangles("../scene/scene_01_fix.scene");
	grid_ptr->setup_cells();

	add_object(grid_ptr);

	open_window(width, height);
}

void World::render_scene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glm::vec3 pixel_color = BLACK;
	
	Ray ray;
	double zw = 100.0;
	double x, y;
	float s = vp.get_pixel_size();
	glm::dvec2 sp;	// sample point in a unit square

	ray.d = glm::dvec3(0, 0, -1);	//光线垂直向屏幕内部

	for (int r=0; r < vp.vres; r++)	// row
	{
		for (int c = 0; c < vp.hres; c++) {
			// 像素坐标(c, r)转世界坐标(x, y); 其中像素坐标以左下角为原点
			// 抖动随机采样
			

			for (int p = 0; p < vp.get_num_samples(); p++) {
				sp = vp.sampler_ptr->sample_unit_square();
				x = s * (c - 0.5*vp.hres + sp.x);
				y = s * (r - 0.5*vp.vres + sp.y);

				ray.o = glm::dvec3(x, y, zw);
				pixel_color = (pixel_color + tracer_ptr->trace_ray(ray));
				// pixel_color = tracer_ptr->trace_ray(ray);
				// display_pixel(r, c, pixel_color);

			}
			//x = s * (c - vp.hres / 2.0 + 0.5);	
			//y = s * (r - vp.vres / 2.0 + 0.5);
			pixel_color = ((1.0f / vp.get_num_samples()) * pixel_color);
			display_pixel(r, c, pixel_color);
		}
	}

	glDrawPixels(vp.hres, vp.vres, GL_RGB, GL_UNSIGNED_BYTE, frame_buffer);
	glutSwapBuffers();
}

void World::render_perspective()
{
	if (camera_ptr)
	{
		camera_ptr->render_scene(*this);
		return;
	}

	glClear(GL_COLOR_BUFFER_BIT);
	glm::vec3 pixel_color = BLACK;

	float s = vp.get_pixel_size();

	float eye = 500;
	float d = 850;

	Ray ray;
	ray.o = glm::dvec3(0.0, 0.0, eye);

	for (int r = 0; r < vp.vres; r++)
	{
		for (int c = 0; c < vp.hres; c++)
		{
			ray.d = glm::dvec3(s*(c - 0.5*(vp.hres - 1.0)),
				s*(r - 0.5*(vp.vres - 1.0)),
				-d);
			ray.d = glm::normalize(ray.d);
			pixel_color = tracer_ptr->trace_ray(ray);
			display_pixel(r, c, pixel_color);

			printf("(%d,%d)\n", c, r);
		}
	}

	glDrawPixels(vp.hres, vp.vres, GL_RGB, GL_UNSIGNED_BYTE, frame_buffer);
	glutSwapBuffers();
}

void World::open_window(const int hres, const int vres) const
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(hres, vres);
	glutCreateWindow("SingleSphere Tracer");

	printf("World::open_window:finish glut init...\n");
}

void World::display_pixel(int row, int col, const glm::vec3& color)
{
	glm::vec3 temp = color;

	temp.x = color.x < 0.0 ? 0.0 : color.x;
	temp.y = color.y < 0.0 ? 0.0 : color.y;
	temp.z = color.z < 0.0 ? 0.0 : color.z;

	float max_component = max(color.x, max(color.y, color.z));
	if (max_component > 1.0 && max_component>kEpsilon)
		temp = (1.0f / max_component) * temp;
	frame_buffer[row * vp.hres * 3 + col * 3 + 0] = (GLubyte)(temp.x * 255);
	frame_buffer[row * vp.hres * 3 + col * 3 + 1] = (GLubyte)(temp.y * 255);
	frame_buffer[row * vp.hres * 3 + col * 3 + 2] = (GLubyte)(temp.z * 255);
}

ShadeRec World::hit_bare_bones_objects(const Ray& ray)
{
	ShadeRec sr(*this);
	double t;
	double tmin = kHugeValue;
	int num_objects = objects.size();

	for (int j = 0; j < num_objects; j++) {
		if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
			sr.hit_an_object = true;
			tmin = t;
			sr.color = objects[j]->get_color();
		}
	}

	return sr;
}

ShadeRec World::hit_objects(const Ray& ray)
{
	ShadeRec sr(*this);
	double t;
	glm::vec3 normal;
	glm::vec3 local_hit_points;
	float tmin = kHugeValue;
	int num_objects = objects.size();

	for (int j = 0; j < num_objects; j++) {
		if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
			sr.hit_an_object = true;
			tmin = t;
			sr.material_ptr = objects[j]->get_material();
			sr.hit_point = ray.o + t * ray.d;
			sr.color = glm::vec3(1, 0, 0);
			sr.hit_object_id = objects[j]->object_id;
			normal = sr.normal;
			local_hit_points = sr.local_hit_point;

			// printf("ray:(%f %f %f) hit id: %d\n", ray.d.x, ray.d.y, ray.d.z, sr.hit_object_id);
		}
	}

	//???
	if (sr.hit_an_object)
	{
		sr.t = tmin;
		sr.normal = normal;
		sr.local_hit_point = local_hit_points;
	}
	return sr;
}

