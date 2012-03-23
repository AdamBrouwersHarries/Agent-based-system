#include <iostream>
#include "graph.h"

int main(int argc, char** argv)
{
	graph g;
	g.initialise(10,10);
	g.connect();
	g.test();
	return 0;
}