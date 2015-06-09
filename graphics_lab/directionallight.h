#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H
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

class DirectionalLight
{
public:
	bool shadow;
	Color irradiance;
	Vector3 direction;
	Vector3 L;
	DirectionalLight(const Color &_irradiance, const Vector3 &_direction, bool _shadow = true):
	irradiance(_irradiance), direction(_direction), shadow(_shadow), L(direction.normalize().negate()) { }
	LightSample sample(Geometry *geometry, const Vector3 &position)
	{
		if (shadow)
		{
			Ray shadow_ray(position, L);
			IntersectResult shadow_result = geometry->intersect(shadow_ray);
			if (shadow_result.geometry)
				return zero;

		}
		return LightSample(L, irradiance);
	}
};

#endif