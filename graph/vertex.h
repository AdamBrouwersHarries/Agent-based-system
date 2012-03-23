/* 
 * File:   vertex.h
 * Author: Adam Harries
 * Stores a vertex within the graph. 
 * Optional cartesian location based upon simple point.
 * Created on 11 February 2012, 23:58
 */
 
#include "../simple_geometry/s_point.h"
#include "../utility/storage_structures/Linked_list/linkedlist.h"

#ifndef VERTEX_H
#define	VERTEX_H

class vertex {
public:

		vertex() {
		}
		vertex(double x, double y)
		{
			location.x = x;
			location.y = y;
		}
		virtual ~vertex() {
		}
		void add_adj(vertex* n)
		{
			adjacent.add_node(n);
		}
		s_point location;
		linkedlist<vertex*> adjacent;
		int id;
};

#endif	/* VERTEX_H */

