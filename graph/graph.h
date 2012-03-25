/* 
 * File:   graph.h
 * Author: adam harries
 *
 * Created on 11 February 2012, 23:57
 */

#include "../utility/storage_structures/linked_list/linkedlist.h"
#include "vertex.h"
//#include "../voronoi_generator/VoronoiDiagramGenerator.cpp"

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
		void initialise(int width, int height, int v_count)
		{
			delete[] verticies;
			vertex_count = v_count;
			verticies = new vertex[vertex_count];
			for(int i = 0;i<vertex_count;i++)
			{
				verticies[i].location.x = (double)(rand()%width);
				verticies[i].location.y = (double)(rand()%height);			
				verticies[i].id = i;
			}
			g_width = width;
			g_height = height;
		}
		void connect() {
		}
		vertex* verticies;
		int vertex_count;
private:
		int g_width, g_height;
};

#endif	/* GRAPH_H */

