#ifndef __VIEW_PLANE_H__
#define __VIEW_PLANE_H__

class ViewPlane
{
public:
	int hres;
	int vres;
	float s;	// pixel size
	float gamma; // monitor gamma factor
	float inv_gamma;	// one over gamma

	ViewPlane();;
	void set_hres(const int h_res);
	void set_vres(const int v_res);
	void set_pixel_size(const float size);
	void set_gamma(const float g);
	
	float get_pixel_size() const { return pixel_size_; }

private:
	float pixel_size_;
};

inline void ViewPlane::set_hres(const int h_res) {
	hres = h_res;
}

inline void ViewPlane::set_vres(const int v_res) {
	vres = v_res;
}

inline void ViewPlane::set_pixel_size(const float size) {
	pixel_size_ = size;
}

inline void ViewPlane::set_gamma(const float g) {
	gamma = g;
	inv_gamma = 1.0 / gamma;
}

#endif // !__VIEW_PLANE_H__
