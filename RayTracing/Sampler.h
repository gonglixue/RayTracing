#ifndef __SAMPLER_H__
#define __SAMPLER_H__

#include <vector>
#include <math.h>

#include "Maths.h"

class Sampler {
public:
	Sampler();
	Sampler(const int num);
	Sampler(const int num, const int num_sets);
	Sampler(const Sampler& s);

	Sampler& operator= (const Sampler& rhs);
	virtual ~Sampler();

	void set_num_sets(const int np);

	int get_num_samples();
	
	virtual void generate_samples() = 0;
	void shuffle_x_coordinates();
	void shuffle_y_coordinates();
	void shuffle_samples();
	void setup_shuffled_indices();

	void map_samples_to_unit_disk(); //?
	void map_samples_to_hemisphere(const float p);
	void map_sampels_to_sphere();
	
	glm::dvec2 sample_unit_square();

protected:
	int num_samples;					// the number of sample points in a set
	int num_sets;
	std::vector<glm::dvec2> samples;	// sample points on a unit square
	std::vector<int> shuffled_indices;
	unsigned long count;	// the current number of sample points used
	int jump;				// random index jump

};

#endif // !__SAMPLER_H__
