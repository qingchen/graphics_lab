#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H
#include "vector3.h"
#include "ray.h"


const double Pi = 3.14159;
class PerspectiveCamera
{
public:
	double fov, fovscale;
	Vector3 eye;
	Vector3 front;
	Vector3 up;
	Vector3 right;
	PerspectiveCamera(const Vector3& _eye, const Vector3& _front, const Vector3& _up, double _fov):eye(_eye), front(_front), up(_up), fov(_fov){}
	void Initialize(){right = front.cross(up); fovscale = tan(fov * 0.5 * Pi / 180) * 2;}
	Ray generateRay(double x, double y)
	{
		Vector3 r = right.multiply((x-0.5)*fovscale);
		Vector3 u = up.multiply((y-0.5)*fovscale);
		return Ray(eye, front.add(r).add(u).normalize());
	}
};
#endif