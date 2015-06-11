#ifndef LIGHT_H
#define LIGHT_H
#include "vector3.h"
#include "color.h"
#include "geometry.h"

class LightSample
{
public:
	Vector3 L;
	Color EL;
	LightSample(const Vector3 &_L, const Color &_EL) : L(_L), EL(_EL) { }
	bool operator==(const LightSample &rhs)
	{
		return this->EL == rhs.EL && this->L == rhs.L;
	}
	bool operator!=(const LightSample &rhs)
	{
		return !(*this == rhs);
	}
};
LightSample zero(Vector3(0, 0, 0), black);

class Light
{
public:
	virtual LightSample sample(Geometry *geometry, const Vector3 &position) = 0;
	virtual ~Light() { };
};

#endif