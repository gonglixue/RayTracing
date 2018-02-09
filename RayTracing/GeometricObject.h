#ifndef __GEOMETRIC_OBJECT_H__
#define __GEOMETRIC_OBJECT_H__

#include <math.h>

#include "Constants.h"
#include "BBox.h"
#include "Ray.h"
#include "ShadeRec.h"

class Material;

class GeometricObject
{
public:
	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr);

protected:
	glm::vec3 color;
};

#endif