#include "ViewPlane.h"

ViewPlane::ViewPlane()
	:hres(400), vres(400),
	gamma(1.0), inv_gamma(1.0),
	num_samples(4)
{}

void ViewPlane::set_sampler(Sampler* _sampler)
{
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	num_samples = _sampler->get_num_samples();
	sampler_ptr = _sampler;
}

//Sampler* ViewPlane::get_sampler()
//{
//	return sampler_ptr_;
//}