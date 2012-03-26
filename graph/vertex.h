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
			visit_count = 3;
		}
		vertex(double x, double y)
		{
			visit_count = 3;
			location.x = x;
			location.y = y;
		}
		virtual ~vertex() {
		}
		void add_adj(vertex* n)
		{
			adjacent.add_node(n);
		}
		vertex* least_visited_neighbour()
		{
			if(adjacent.dummy_start.next_ptr != &(adjacent.dummy_end))
			{
				vertex* lowest_node = adjacent.dummy_start.next_ptr->payload;
				int lowest_visit_count = lowest_node->visit_count;
				for(llnode<vertex*>* iter = adjacent.dummy_start.next_ptr;iter!=&(adjacent.dummy_end);iter=iter->next_ptr)
				{
					if(iter->payload->visit_count < lowest_visit_count)
					{
						lowest_node = iter->payload;
						lowest_visit_count = lowest_node->visit_count;
					}
				}
				return lowest_node;
			}else{
				return this;
			}
		}
		s_point location;
		linkedlist<vertex*> adjacent;
		int id;
		//basic agent pathfinding information
		int visit_count;
};

#endif	/* VERTEX_H */

