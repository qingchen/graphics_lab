#include <math.h>
#ifndef COLOR_H
#define COLOR_H


class Color
{
public:
	double r, g, b;
	Color(double _r, double _g, double _b):r(_r), g(_g), b(_b){}
	Color add(const Color &c) {return Color(r+c.r, g+c.g, b+c.b);}
	Color multiply(double c) {return Color(r*c, g*c, b*c);}
	Color modulate(const Color &c) {return Color(r*c.r, g*c.g, b*c.b);}
};
Color black = Color(0, 0, 0);
Color white = Color(1, 1, 1);
Color red = Color(1, 0, 0);
Color green = Color(0, 1, 0);
Color blue = Color(0, 0, 1);
#endif