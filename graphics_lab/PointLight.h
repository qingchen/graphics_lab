#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "light.h"

class PointLight: public Light
{
public:
	Color intensity;
	Vector3 position;
	bool shadow;
	PointLight(const Color &_intensity, const Vector3 &_position, bool _shadow = true):
	intensity(_intensity), position(_position), shadow(_shadow) { }
	LightSample sample(Geometry *geometry, const Vector3 &position)
	{
		Vector3 delta = this->position.subtract(position);
		double rr = delta.sqrLength();
		double r = sqrt(rr);
		Vector3 L = delta.divide(r);

		if (shadow)
		{
			Ray shadow_ray(position, L);
			IntersectResult shadow_result = geometry->intersect(shadow_ray);
			if (shadow_result.geometry && shadow_result.distance <= r)
				return zero;
		}

		double attenuation = 1 / rr;
		return LightSample(L, intensity.multiply(attenuation));
	}
};
#endif