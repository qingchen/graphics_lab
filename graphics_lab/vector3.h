#include <math.h>
#ifndef VECTOR3_H
#define VECTOR3_H



class Vector3
{
public:
	double x, y, z;
	Vector3(const Vector3& v):x(v.x), y(v.y), z(v.z){}
	Vector3(double _x = 0, double _y = 0, double _z = 0):x(_x), y(_y), z(_z){}
	double length() const {return sqrt(x * x + y * y + z * z);}
	double sqrLength() const {return x * x + y * y + z * z;}
	Vector3 normalize() const {double inv = 1 / length(); return Vector3(x * inv, y * inv, z * inv);}
	Vector3 negate() const {return Vector3(-x, -y, -z);}
	Vector3 add(const Vector3 &lhs) const {return Vector3(x + lhs.x, y + lhs.y, z + lhs.z);}
	Vector3 subtract(const Vector3 &lhs) const {return Vector3(x - lhs.x, y - lhs.y, z - lhs.z);}
	Vector3 multiply(double f)const {return Vector3(x * f, y * f, z * f);}
	Vector3 divide(double f){double inv = 1 / f; return Vector3(x * inv, y * inv, z * inv);}
	double dot(const Vector3 &lhs) const {return x * lhs.x + y * lhs.y + z * lhs.z;}
	Vector3 cross(const Vector3 &lhs) const {return Vector3(-z * lhs.y + y * lhs.z, z * lhs.x - x * lhs.z, -y * lhs.x + x * lhs.y);}

};
Vector3  zero = Vector3(0, 0, 0);
#endif