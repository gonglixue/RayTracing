#include "Constants.h"
#include <glm/glm.hpp>
#include "Pinhole.h"
#include "Sampler.h"

Pinhole::Pinhole()
	:Camera(),
	d(500),
	zoom(1.0)
{

}

Pinhole::Pinhole(const Pinhole& c)
	:Camera(c),
	d(c.d),
	zoom(c.zoom)
{

}

Camera*
Pinhole::clone(void) const {
	return (new Pinhole(*this));
}


Pinhole& Pinhole::operator= (const Pinhole& rhs)
{
	if (this == &rhs)
		return (*this);

	Camera::operator=(rhs);
	d = rhs.d;
	zoom = rhs.zoom;

	return (*this);
}

Pinhole::~Pinhole()
{

}

// p是像素坐标，返回方向的世界坐标
glm::dvec3 Pinhole::get_direction(const glm::vec2 p) const
{
	glm::dvec3 dir = p.x * u + p.y * v - d*w;
	dir = glm::normalize(dir);

	return (dir);
}

void Pinhole::render_scene(World& w)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glm::vec3 pixel_color = BLACK;

	ViewPlane vp(w.get_viewplane());
	Ray ray;
	int depth = 0;
	glm::dvec2 pp;		// sample point on a pixel
	glm::vec2 sp;

	int n = (int)sqrt((float)vp.get_num_samples());
	// int n = 2;
	
	float pix_size = vp.get_pixel_size() / zoom;
	ray.o = eye;

	for (int r = 0; r < vp.vres; r++)
	{
		for (int c = 0; c < vp.hres; c++) {
			pixel_color = BLACK;
			/*
			for (int p = 0; p < n; p++)
			{
				for (int q = 0; q < n; q++)
				{
					pp.x = pix_size * (c - 0.5 * vp.hres + (q + 0.5) / n);
					pp.y = pix_size * (r - 0.5 * vp.vres + (p + 0.5) / n);
					ray.d = get_direction(pp);
					pixel_color = pixel_color + w.get_tracer()->trace_ray(ray, 0);
				}
			}
			*/

			for (int j = 0; j < vp.get_num_samples(); j++)
			{
				sp = vp.sampler_ptr->sample_unit_square();
				pp.x = pix_size * (c - 0.5*vp.hres + sp.x);
				pp.y = pix_size * (r - 0.5*vp.vres + sp.y);
				ray.d = get_direction(pp);

				pixel_color = pixel_color + w.get_tracer()->trace_ray(ray, 0);
			}

			pixel_color = (1.0f / (vp.get_num_samples())) * pixel_color;
			pixel_color = exposure_time * pixel_color;
			w.display_pixel(r, c, pixel_color);
		}
	}


	w.draw_framebuffer();

}