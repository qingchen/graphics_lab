#include "vector3.h"
#include "color.h"
#include "ray.h"
#include "material.h"

#ifndef PHONGMATERIAL_H
#define PHONGMATERIAL_H

Vector3 lightDir = Vector3(1, 1, 1).normalize();
Color lightColor = white;

class PhongMaterial:public Material
{
public:
	Color diffuse;
	Color specular;
	double shininess;
	PhongMaterial(const Color &_diffuse, const Color &_specular, double _shininess, double _reflectiveness = 0)
		:diffuse(_diffuse), specular(_specular), shininess(_shininess), Material(_reflectiveness){}
	virtual Color sample(const Ray &ray, const Vector3 &position, const Vector3 &normal)
	{
		double NdotL = normal.dot(lightDir);
		Vector3 H = (lightDir.subtract(ray.direction)).normalize();
		double NdotH = normal.dot(H);
		Color diffuseTerm = diffuse.multiply(max(NdotL, 0));
		Color specularTerm = specular.multiply(pow(max(NdotH,0), shininess));
		return lightColor.modulate(diffuseTerm.add(specularTerm));
	}
};
#endif