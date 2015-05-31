#include "vector3.h"

class Ray
{
public:
	Vector3 origin, direction;
	Ray(){}
	Ray(const Vector3& _origin, const Vector3& _direction):origin(_origin), direction(_direction){}
	Vector3 getPoint(double t){return origin.add(direction.multiply(t));}
};