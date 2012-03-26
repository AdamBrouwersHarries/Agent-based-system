#ifndef AGENT_H
#define AGENT_H
#include "../utility/general_includes.h"
#include "../graph/graph.h"
class agent
{
public:
	agent()
	{
		running = false;
		current_location = s_point(0,0);
		velocity = s_point(0,0);
		acceleration = s_point(0,0);
	}
	agent(vertex* fv)
	{
		running = false;
		current_location = s_point(0,0);
		velocity = s_point(0,0);
		acceleration = s_point(0,0);
		current_node = fv;
	}
	virtual ~agent(){}
	void simulate()
	{
		if(running == true)
		{
			if(current_location.m_is_near(current_node->location, 4))
			{
				//set a new target
				if(current_node->least_visited_neighbour()!=current_node)
				{
					current_node->visit_count = current_node->visit_count +1;
				}
				find_new_target();
			}else{
				//current_location.x += (current_node->location.x - current_location.x)/10;
				//current_location.y += (current_node->location.y - current_location.y)/10;
				
			}
			s_point displacement_vector = current_node->location - current_location;
				//calculate the acceleration (constant) towards the node, by normalising the vector to it.
				acceleration = (displacement_vector/(current_node->location.distance(current_location)))/100;
				velocity = velocity +acceleration;
				velocity = velocity - (velocity/100);
				current_location=current_location+velocity;
		}
	}
	void draw()
	{
		draw_square(current_location.x, current_location.y,3);
		glColor4f(1.0,0.0,0.0,0.4);
		glBegin(GL_LINES);
			glVertex2f(current_location.x, current_location.y);
			glVertex2f(current_location.x+(velocity.x*10), current_location.y+(velocity.y*10));
			glColor4f(1.0,0.8f,0.0,0.4);
			glVertex2f(current_location.x, current_location.y);
			glVertex2f(current_location.x+(acceleration.x*1000), current_location.y+(acceleration.y*1000));
			glColor4f(0.0,1.0,0.0,0.5);
			//glVertex2f(current_location.x, current_location.y);
			//glVertex2f(current_node->location.x, current_node->location.y);
			/*glVertex2f(current_node->location.x, current_node->location.y);
			for(unsigned int i = 0;i<future_locations.size();i++)
			{
				vertex* loc = future_locations[i];
				glVertex2f(loc->location.x, loc->location.y);
				glVertex2f(loc->location.x, loc->location.y);
			}*/
		glEnd();
		glColor4f(1.0,1.0,1.0,1.0);
	}
	void find_new_target()
	{
		future_locations.clear();
		current_node = current_node->least_visited_neighbour();
		vertex* iter_node = current_node;
		for(int i = 0;i<5;i++)
		{
			iter_node = iter_node->least_visited_neighbour();
			future_locations.push_back(iter_node);
		}
	}
	s_point current_location;
	s_point velocity;
	s_point acceleration;
	std::vector<vertex*> future_locations;
	vertex* current_node;
	graph* agent_graph;
	bool running;
private:
};
#endif //AGENT_H