#include "ray.h"
#include "vector3.h"
#ifndef SPHERE_H
#define SPHERE_H


struct IntersectResult
{
	bool hit;
	double distance;
	Vector3 position;
	Vector3 normal;
	IntersectResult(bool _hit = false, double _distance = 0, Vector3 _position = Vector3(0, 0, 0), Vector3 _normal = Vector3(0, 0, 0)):hit(_hit), distance(_distance), position(_position), normal(_normal){}
};

class Sphere
{
public:
	Vector3 center;
	double radius, sqr_radius;
	Sphere(const Vector3 &_center, double _radius):center(_center), radius(_radius), sqr_radius(_radius*_radius){}
	IntersectResult intersect(Ray ray)
	{
		Vector3 v = ray.origin.subtract(center);
		double a0 = v.sqrLength() - sqr_radius;
		double dotv = ray.direction.dot(v);
		IntersectResult result;
		if (dotv <= 0)
		{
			double discr = dotv * dotv - a0;
			if (discr >= 0)
			{
				result.hit = true;
				result.distance = -dotv - sqrt(discr);
				result.position = ray.getPoint(result.distance);
				result.normal = result.position.subtract(center).normalize();
			}
		}
		return result;
	}
};
#endif