#ifndef __NROOKS_H__
#define __NROOKS_H__

#include "Sampler.h"

class NRooks : public Sampler
{
public:
	NRooks();
	NRooks(const int _num_samples);
	NRooks(const int _num_samples, const int _num_sets);
	NRooks(const NRooks& nrooks);

	NRooks& operator= (const NRooks& rhs);
	virtual ~NRooks();

private:
	virtual void generate_samples();
};


#endif // !__NROOKS_H__
