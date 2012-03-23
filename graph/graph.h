/* 
 * File:   graph.h
 * Author: adam harries
 *
 * Created on 11 February 2012, 23:57
 */

#include "../utility/storage_structures/linked_list/linkedlist.h"
#include "vertex.h"

#ifndef GRAPH_H
#define	GRAPH_H

class graph {
public:

		graph() {
			verticies = new vertex[2];
		}

		virtual ~graph() {
			delete[] verticies;
		}
		void initialise(int width, int height)
		{
			delete[] verticies;
			vertex_count = 10;
			verticies = new vertex[vertex_count];
			for(int i = 0;i<vertex_count;i++)
			{
				verticies[i].location.x = (double)(rand()%width);
				verticies[i].location.y = (double)(rand()%height);			
				verticies[i].id = i;
			}
		}
		void connect() {
			for(int i = 0;i<vertex_count;i++)
			{
				for(int j = i;j<vertex_count;j++)
				{
					if(i!=j)
					{
						vertex* a = &(verticies[i]);
						vertex* b = &(verticies[j]);
						a->adjacent.add_node(b);
						b->adjacent.add_node(a);
					}
				}
			}
		}
		vertex* verticies;
		int vertex_count;
private:
};

#endif	/* GRAPH_H */

