#include "vector3.h"

class Ray
{
public:
	Vector3 origin, direction;
	Ray(Vector3 _origin, Vector3 _direction):origin(_origin), direction(_direction){}
	Vector3 getPoint(double t){return origin.add(direction.multiply(t));}
};