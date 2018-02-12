#include "World.h"
#include "SingleSphere.h"
#include "MultipleObjects.h"
#include "ShadeRec.h"
#include "Plane.h"

World::World()
	:background_color(BLACK),
	frame_buffer(NULL)
{}

World::~World()
{}

void World::build(const int width, const int height)
{
	printf("begin build...\n");
	vp.set_hres(width);
	vp.set_vres(height);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);

	frame_buffer = (GLubyte*)malloc(vp.hres*vp.vres * 3 * sizeof(GLubyte));
	background_color = BLACK;
	//tracer_ptr = new SingleSphere(this);
	tracer_ptr = new MultipleObjects(this);

	/*sphere_.set_center(0.0, 0.0, 0.0);
	sphere_.set_radius(85.0);*/
	// world objects
	Sphere* sphere_ptr = new Sphere;
	sphere_ptr->set_center(0, -25, 0);
	sphere_ptr->set_radius(80.0);
	sphere_ptr->set_color(1, 0, 0);
	add_object(sphere_ptr);

	//delete sphere_ptr;
	sphere_ptr = new Sphere(glm::dvec3(0, 20, 0), 60);
	sphere_ptr->set_color(1, 1, 0); //yellow
	add_object(sphere_ptr);

	Plane* plane_ptr = new Plane(glm::dvec3(0), glm::dvec3(0, 1, 1));
	plane_ptr->set_color(0, 0.35, 0);//dark green
	add_object(plane_ptr);

	open_window(width, height);
}

void World::render_scene()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glm::vec3 pixel_color;
	Ray ray;
	double zw = 100.0;
	double x, y;
	float s = vp.get_pixel_size();

	ray.d = glm::dvec3(0, 0, -1);	//光线垂直向屏幕内部

	for (int r=0; r < vp.vres; r++)	// row
	{
		for (int c = 0; c < vp.hres; c++) {
			// 像素坐标(c, r)转世界坐标(x, y); 其中像素坐标以左下角为原点
			x = s * (c - vp.hres / 2.0 + 0.5);	
			y = s * (r - vp.vres / 2.0 + 0.5);

			ray.o = glm::dvec3(x, y, zw);
			pixel_color = tracer_ptr->trace_ray(ray);
			display_pixel(r, c, pixel_color);
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
	frame_buffer[row * vp.hres * 3 + col * 3 + 0] = (GLubyte)(color.x * 255);
	frame_buffer[row * vp.hres * 3 + col * 3 + 1] = (GLubyte)(color.y * 255);
	frame_buffer[row * vp.hres * 3 + col * 3 + 2] = (GLubyte)(color.z * 255);
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

