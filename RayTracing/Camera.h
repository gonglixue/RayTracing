#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm/glm.hpp>
class World;

class Camera {
public:
	Camera();
	Camera(const Camera& camera);
	virtual Camera*							// virtual copy constructor
		clone(void) const = 0;

	virtual
		~Camera();
	virtual void
		render_scene(World& w) = 0;
	void set_eye(const glm::vec3 p);
	void set_eye(float x, float y, float z);
	void set_lookat(const glm::vec3 p);
	void set_lookat(float x, float y, float z);
	void set_up_vector(const glm::vec3 u);
	void set_up_vector(float x, float y, float z);

	void set_roll(float roll);
	void set_exposure_time(const float exposure);
	void compute_uvw(void);

protected:
	glm::vec3 eye;
	glm::vec3 lookat;
	float ra;	//roll angle
	glm::vec3 u;
	glm::vec3 v;
	glm::vec3 w;	// orthonormal basis vectors:视线方向的逆方向
	glm::vec3 up;
	float exposure_time;

	Camera& operator= (const Camera& camera);
};

inline void
Camera::set_eye(const glm::vec3 p)
{
	eye = p;
}

inline void 
Camera::set_eye(float x, float y, float z)
{
	eye = glm::vec3(x, y, z);
}

inline void 
Camera::set_lookat(glm::vec3 p)
{
	lookat = p;
}

inline void
Camera::set_lookat(float x, float y, float z)
{
	lookat = glm::vec3(x, y, z);
}

inline void 
Camera::set_up_vector(const glm::vec3 p)
{
	up = p;
}

inline void 
Camera::set_up_vector(float x, float y, float z)
{
	up = glm::vec3(x, y, z);
}

inline void 
Camera::set_roll(float r)
{
	ra = r;
}

inline void 
Camera::set_exposure_time(float exposure)
{
	exposure_time = exposure;
}

#endif // !__CAMERA_H__
