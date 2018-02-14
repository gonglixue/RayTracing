#ifndef __JITTERED_H__
#define __JITTERED_H__

#include "Sampler.h"

class Jittered :public Sampler
{
public:
	Jittered();
	Jittered(const int _num_samples);
	Jittered(const int _num_samples, const int _num_sets);
	Jittered(const Jittered& jitter);

	Jittered& operator= (const Jittered& rhs);
	virtual ~Jittered();

private:
	virtual void generate_samples();
};
#endif // !__JITTERED_H__
