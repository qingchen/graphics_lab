#include "ray.h"
#include "vector3.h"
#include "intersectresult.h"
#include "geometry.h"
#ifndef SPHERE_H
#define SPHERE_H

class Sphere:public Geometry
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
				result.geometry = this;
				result.distance = -dotv - sqrt(discr);
				result.position = ray.getPoint(result.distance);
				result.normal = result.position.subtract(center).normalize();
				return result;
			}
		}
		return result.noHit();
	}
};
#endif