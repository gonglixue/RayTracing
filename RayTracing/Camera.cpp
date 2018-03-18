#include "Camera.h"

Camera::Camera(void)
	: eye(0, 0, 500),
	lookat(0, 0, 0),
	ra(0),
	u(1, 0, 0),
	v(0, 1, 0),
	w(0, 0, 1),
	up(0, 1, 0),
	exposure_time(1.0)
{

}

Camera::Camera(const Camera& c)
	:eye(c.eye),
	lookat(c.lookat),
	ra(c.ra),
	u(c.u),
	v(c.v),
	w(c.w),
	up(c.up),
	exposure_time(c.exposure_time)
{

}

Camera&
Camera::operator= (const Camera& rhs)
{
	if (this == &rhs)
		return (*this);

	eye = rhs.eye;
	lookat = rhs.lookat;
	ra = rhs.ra;
	up = rhs.up;
	u = rhs.u;
	v = rhs.v;
	w = rhs.w;
	exposure_time = rhs.exposure_time;

	return (*this);
}

Camera::~Camera()
{

}

// 通过给定的视点位置、lookat、up来计算相机坐标系的基
void Camera::compute_uvw()
{
	w = eye - lookat;
	w = glm::normalize(w);
	u = glm::cross(up, w);
	u = glm::normalize(u);
	v = glm::cross(w, u);

	// 垂直向下看
	if (eye.x == lookat.x
		&& eye.z == lookat.z
		&& eye.y > lookat.y)
	{
		u = glm::vec3(0, 0, 1);
		v = glm::vec3(1, 0, 0);
		w = glm::vec3(0, 1, 0);
	}

	// 垂直向上看
	if (eye.x == lookat.x
		&& eye.z == lookat.z
		&& eye.y < lookat.y)
	{
		u = glm::vec3(1, 0, 0);
		v = glm::vec3(0, 0, 1);
		w = glm::vec3(0, -1, 0);
	}
}