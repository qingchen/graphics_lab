#include "material.h"
#ifndef GEOMETRY_H
#define GEOMETRY_H

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
};
#endif