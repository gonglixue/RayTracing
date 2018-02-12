#include "World.h"
#include "SingleSphere.h"

World::World()
	:background_color(BLACK),
	frame_buffer(NULL)
{}

World::~World()
{}

void World::build()
{
	vp.set_hres(200);
	vp.set_vres(200);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);

	frame_buffer = (GLubyte*)malloc(vp.hres*vp.vres * 3 * sizeof(GLubyte));
	background_color = BLACK;
	tracer_ptr = new SingleSphere(this);

	sphere.set_center(0.0, 0.0, 0.0);
	sphere.set_radius(85.0);
}

void World::render_scene()
{
	glm::vec3 pixel_color;
	Ray ray;
	double zw = 100.0;
	double x, y;
	open_window(vp.hres, vp.vres);
	ray.d = glm::dvec3(0, 0, -1);	//光线垂直向屏幕内部

	for (int r=0; r < vp.vres; r++)	// row
	{
		for (int c = 0; c < vp.hres; c++) {
			// 像素坐标(c, r)转世界坐标(x, y); 其中像素坐标以左下角为原点
			x = vp.s * (c - vp.hres / 2.0 + 0.5);	
			y = vp.s * (r - vp.vres / 2.0 + 0.5);

			ray.o = glm::dvec3(x, y, zw);
			pixel_color = tracer_ptr->trace_ray(ray);
			display_pixel(r, c, pixel_color);
		}
	}
}

void World::open_window(const int hres, const int vres) const
{
	glutInit(0, 0);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(hres, vres);
	glutCreateWindow("SingleSphere Tracer");

}

void World::display_pixel(int row, int col, const glm::vec3& color)
{
	frame_buffer[row * vp.hres * 3 + col * 3 + 0] = (GLubyte)(color.x * 255);
	frame_buffer[row * vp.hres * 3 + col * 3 + 1] = (GLubyte)(color.y * 255);
	frame_buffer[row * vp.hres * 3 + col * 3 + 2] = (GLubyte)(color.z * 255);
}

