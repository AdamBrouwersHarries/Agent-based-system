#ifndef S_POINT_H
#define S_POINT_H
#include "../utility/general_includes.h"
class s_point
{
public:
	s_point(){}
	s_point(double nx, double ny){x=nx;y=ny;}
	virtual ~s_point(){}
	double x, y;
	
	//distance methods
	double distance(s_point other)
	{
		double diffx = other.x-x;
		double diffy = other.y-y;
		return sqrt((diffx*diffx)+(diffy*diffy));
	}
	double distance(double nx, double ny)
	{
		double diffx = nx-x;
		double diffy = ny-y;
		return sqrt((diffx*diffx)+(diffy*diffy));
	}
	//uses manhatten distances to determine if the point is "near" another point
	//essentially checks to see if both x and y difference are within a certain tolerance
	bool m_is_near(s_point other, double tolerance)
	{
		double dx = abs(other.x-x);
		double dy = abs(other.y-y);
		return (dx<tolerance && dy<tolerance);
	}
	//equality operators
	bool operator==(const s_point &other) const {
		return (other.x==x)&&(other.y==y);
	}
	bool operator!=(const s_point &other) const {
		return !(*this == other);
	}	
};
#endif //S_POINT_H