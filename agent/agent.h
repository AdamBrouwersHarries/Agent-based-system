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
	}
	virtual ~agent(){}
	void simulate()
	{
		if(running == true)
		{
			if(current_location.m_is_near(current_node->location, 4))
			{
				//set a new target
				current_node = (current_node->adjacent.dummy_start.next_ptr)->payload;
			}else{
				current_location.x += (current_node->location.x - current_location.x)/10;
				current_location.y += (current_node->location.y - current_location.y)/10;
			}
		}
	}
	s_point current_location;
	std::vector<vertex*> future_locations;
	vertex* current_node;
	graph* agent_graph;
	bool running;
private:
};
#endif //AGENT_H