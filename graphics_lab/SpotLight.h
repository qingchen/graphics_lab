#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H
#include "light.h"

class SpotLight: public Light
{
public:
	Color intensity;
	Vector3 position;
	Vector3 direction;
	Vector3 S;
	double theta, phi, falloff;
	bool shadow;
	double cos_theta, cos_phi, base_multipler;
	SpotLight(const Color &_intensity, const Vector3 &_position, const Vector3 &_direction, double _theta, double _phi, double _falloff, bool _shadow = true):
	intensity(_intensity), position(_position), direction(_direction), theta(_theta), phi(_phi), falloff(_falloff), shadow(_shadow),
	S(direction.normalize().negate()), cos_theta(cos(theta * Pi / 180 / 2)), cos_phi(cos(phi * Pi / 180 / 2)),
	base_multipler(1 / (cos_theta - cos_phi)) { }
	LightSample sample(Geometry *geometry, const Vector3 &position)
	{
		Vector3 delta = this->position.subtract(position);
		double rr = delta.sqrLength();
		double r = sqrt(rr);
		Vector3 L = delta.divide(r);

		double spot;
		double SdotL = S.dot(L);
		if (SdotL >= cos_theta)
			spot = 1;
		else if (SdotL <= cos_phi)
			spot = 0;
		else
			spot = pow((SdotL - cos_phi) * base_multipler, falloff);

		if (shadow)
		{
			Ray shadow_ray(position, L);
			IntersectResult shadow_result = geometry->intersect(shadow_ray);
			if (shadow_result.geometry && shadow_result.distance <= r)
				return zero;
		}

		double attenuation = 1 / rr;

		return LightSample(L, intensity.multiply(attenuation * spot));
	}
};
#endif