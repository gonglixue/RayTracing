#ifndef __JITTERED_H__
#define __JITTERED_H__

#include "Sampler.h"

class Jittered :public Sampler
{
private:
	virtual void generate_samples();
};
#endif // !__JITTERED_H__
