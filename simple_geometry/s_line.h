#ifndef S_LINE_H
#define S_LINE_H
#include "s_point.h"
#include "../utility/general_includes.h"
class s_line
{
public:
	s_line(){}
	virtual ~s_line(){}
	//-----------------
	s_point a, b; 
	s_line(s_point e1, s_point e2){a=e1;b=e2;}
	//returns the slope from a->b
	double d_slope()
	{
		return (a.y-b.y)/(a.x-b.x);
	}
	//returns the 2d vector from a->b
	s_point p_slope()
	{
		return s_point(b.x-a.x, b.y-b.y);
	}
	//returns the midpoint of the line as a 2d point
	s_point midpoint()
	{
		return s_point((a.x+b.x)/2, (a.y+b.y)/2);
	}
	//queries if the line is on the boundary specified by the arguments
	bool boundary_line(double minX, double maxX, double minY, double maxY)
	{
		bool y_boundary = (d_e(a.y,minY) and d_e(b.y,minY))||(d_e(a.y,maxY) and d_e(b.y,maxY));
		bool x_boundary = (d_e(a.x,minX) and d_e(b.x,minX))||(d_e(a.x,maxX) and d_e(b.x,maxX));
		return (x_boundary or y_boundary);
	}
	bool out_of_bounds(double minX, double maxX, double minY, double maxY)
	{
		bool y_out = a.y<maxY and a.y>minY and b.y<maxY and b.y>minY;
		bool x_out = a.x<maxX and a.x>minX and b.x<maxX and b.x>minX;
		return !(y_out or x_out);
	}
	bool boundary_touching(double minX, double maxX, double minY, double maxY)
	{
		bool x_touch = (d_e(a.x, minX) or d_e(a.x,maxX) or d_e(b.x, minX) or d_e(b.x, maxX));
		bool y_touch = (d_e(a.y, minY) or d_e(a.y,maxY) or d_e(b.y, minY) or d_e(b.y, maxY));
		return (x_touch or y_touch);
		
	}
	//equality operators
	bool operator==(const s_line &other) const {
		return (other.a==a)&&(other.b==b);
	}
	bool operator!=(const s_line &other) const {
		return !(*this == other);
	}
};
#endif //S_LINE_H