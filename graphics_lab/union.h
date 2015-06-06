#ifndef UNION_H
#define UNION_H
#include "geometry.h"
#include <vector>

using namespace std;

class Union : public Geometry
{
public:
	vector<Geometry*> geometrys;
	virtual IntersectResult intersect(const Ray &ray)
	{
		double min_distance = 1e30;
		IntersectResult result, min_result;
		for (vector<Geometry*>::size_type i = 0; i < geometrys.size(); i++)
		{
			result = geometrys[i]->intersect(ray);
			if (result.geometry && result.distance < min_distance)
			{
				min_result = result;
				min_distance = result.distance;
			}
		}
		return min_result;
	}
	~Union()
	{
		vector<Geometry*>::size_type n = geometrys.size();
		for (vector<Geometry*>::size_type i = 0; i < n; i++)
			delete geometrys[i];
		geometrys.clear();
	}
};
#endif