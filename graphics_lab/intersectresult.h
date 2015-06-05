#ifndef INTERSECTRESULT_H
#define INTERSECTRESULT_H
#include "vector3.h"
#include "geometry.h"

class IntersectResult
{
public:
	Geometry *geometry;
	double distance;
	Vector3 position;
	Vector3 normal;
	IntersectResult(Geometry *_geometry = 0, double _distance = 0, Vector3 _position = Vector3(0, 0, 0), Vector3 _normal = Vector3(0, 0, 0))
		:geometry(_geometry), distance(_distance), position(_position), normal(_normal){}
	
	//IntersectResult noHit(){return IntersectResult();}
};
IntersectResult noHit;
#endif