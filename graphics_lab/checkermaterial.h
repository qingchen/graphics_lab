#include <math.h>
#include "ray.h"
#include "vector3.h"
#include "color.h"
#include "material.h"

#ifndef CHECKERMATERIAL_H
#define CHECKERMATERIAL_H

class CheckerMaterial:public Material
{
public:
	double scale;
	CheckerMaterial(double _scale, double _reflectiveness = 0):scale(_scale), Material(_reflectiveness){}
	virtual Color sample(const Ray &ray, const Vector3 &position, const Vector3 &normal)
	{
		return abs((int)(floor(position.x * 0.1) + floor(position.z * scale)) % 2) < 1 ? black : white;
	}
};
#endif