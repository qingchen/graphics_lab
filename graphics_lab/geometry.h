#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "material.h"
#include "ray.h"
#include "intersectresult.h"
class IntersectResult;
class Geometry
{
public:
	Material* material;
	Geometry(): material(0){}
	virtual ~Geometry()
	{
		if (material)
			delete material;
	}
	virtual IntersectResult intersect(const Ray &ray) = 0;
};
#endif