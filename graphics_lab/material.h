#include "ray.h"
#include "vector3.h"
#include "color.h"
#ifndef MATERIAL_H
#define MATERIAL_H

class Material
{
public:
	double reflectiveness;
	Material(double _reflectiveness): reflectiveness(_reflectiveness){}
	virtual ~Material(){}
	virtual Color sample(const Ray& ray, const Vector3& position, const Vector3& normal) = 0;
};
#endif