#include "Jittered.h"

// �ڵ�λ������������num_samples * num_sets��������
void Jittered::generate_samples()
{
	int n = (int)sqrt(num_samples);

	for (int p = 0; p < num_sets; p++) {
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++) {
				glm::dvec2 sp((k + rand_float()) / n, (j + rand_float()) / n);
				samples.push_back(sp);
			}
		}
	}
}