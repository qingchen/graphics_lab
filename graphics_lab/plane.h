#ifndef PLANE_H
#define PLANE_H
#include "vector3.h"
#include "geometry.h"
#include "ray.h"

class Plane: public Geometry
{
public:
	Vector3 normal;
	double d;
	Vector3 position;
	Plane(const Vector3 &_normal, double _d):normal(_normal), d(_d), position(normal.multiply(d)){}
	//void initialize(){position = normal.multiply(d);}
	virtual IntersectResult intersect(const Ray &ray)
	{
		double a = ray.direction.dot(normal);
		if (a >= 0)
			return noHit;
		double b = normal.dot(ray.origin.subtract(position));
		IntersectResult result;
		result.geometry = this;
		result.distance = -b / a;
		result.position = ray.getPoint(result.distance);
		result.normal = normal;
		return result;
	}
};
#endif