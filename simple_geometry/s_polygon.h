#ifndef S_POLYGON_H
#define S_POLYGON_H
#include "s_line.h"
#include "../utility/general_includes.h"


//struct used for sorting the edges into clockwise order

struct edge_sorter {

		bool operator ()(s_line a, s_line b) {
				double det = ((a.midpoint().x - centre.x)*(b.midpoint().y - centre.y))-((b.midpoint().x - centre.x)*(a.midpoint().y - centre.y));
				return det > 0;
		}
		s_point centre;
};
struct point_sorter {
		bool operator()(s_point a, s_point b){
				double det = ((a.x-centre.x)*(b.y-centre.y))-((b.x-centre.x)*(a.y-centre.y));
				return det > 0;
		}
		s_point centre;
};

class s_polygon {
public:

		s_polygon() {
		}

		virtual ~s_polygon() {
				e.clear();
		}

		//list of lines in the polygon, arguably better/more space efficient to store as a list of points
		//however this does have other benefits as well, such as easy area calculations...
		std::vector<s_line>e;
		//tentative (temporary) list of VERTICIES for the polygon
		std::vector<s_point>v;
		//add a line, from 2 points

		void add_line(s_point a, s_point b) {
				e.push_back(s_line(a, b));
		}
		//add a line from an already constructed line

		void add_line(s_line d) {
				e.push_back(d);
		}
		void sort_verticies(s_point c){				
				if(e.size()<=0)
				{
						std::cout<<"no edges, breaking...\n";
						return;
				}else{
						point_sorter ps;
						ps.centre = c;
						for(unsigned int i = 0;i<e.size();i++)
						{
								v.push_back(e[i].a);
						}						
						//sort(v.begin(), v.end(),ps);
				}
				
				
		}
		//sort the edges clockwise around given point

		void sort_edges(s_point c) {
				edge_sorter es;
				es.centre = c;
				sort(e.begin(), e.end(), es);
				point_sorter ps;
				ps.centre = c;
				for (unsigned int i = 0; i < e.size(); i++) {
						if (ps(e[i].b, e[i].a)) {
								s_point temp = e[i].a;
								e[i].a = e[i].b;
								e[i].b = temp;
						}
				}
		}

		bool edges_matched() {
				bool unmatched_found = false;
				for (unsigned int i = 0; i < e.size(); i++) {
						bool match_found = false;
						for (unsigned int j = 0; j < e.size(); j++) {
								if (e[j].a == e[i].b || e[j].b == e[i].a || e[j].a == e[i].a || e[j].b == e[i].b)
										match_found = true;
						}
						if (match_found == false)
								unmatched_found = true;
				}
				return !unmatched_found;
		}

		double area(s_point centre) {
				s_point a, b;
				double total = 0;
				for (unsigned int i = 0; i < e.size(); i++) {
						a = e[i].a;
						b = e[i].b;
						total += triangle_area(a, b, centre);
				}
				return total;
		}

		double triangle_area(s_point a, s_point b, s_point c) {
				return (((a.x - c.x)*(b.y - c.y))-((b.x - c.x)*(a.y - c.y))) / 2;
		}

		int point_in_poly(s_point test_point) {
				double nx, ny, x, y;
				//	Clockwise order.

				for (unsigned int i = 0; i < e.size(); i++) {
						//	generate a 2d normal ( no need to normalise ).
						nx = e[i].b.y - e[i].a.y;
						ny = e[i].a.x - e[i].b.x;

						x = test_point.x - e[i].a.x;
						y = test_point.y - e[i].a.y;

						//	Dot with edge normal to find side.
						if ((x * nx) + (y * ny) > 0)
								return 0;
				}

				return 1;
		}
private:
		//calculates if point a is clockwise of point b, with respect to the centre ce

		double clockwise_of(s_point ce, s_point a, s_point b) {
				//((a.midpoint().x-centre.x)*(b.midpoint().y-centre.y))-((b.midpoint().x-centre.x)*(a.midpoint().y-centre.y));
				return ((a.x)*(b.y - ce.y))-((b.x - ce.x)*(a.y - ce.y));
		}
};
#endif //S_POLYGON_H