#include <iostream>

#include "Solver.hpp"
#include "Logger.hpp"

int main(int argc, char const *argv[])
{
	
	ss::Solver solver;
	LOGGER->Log("program initiated...");

	solver.breadthFirst.solve("maps/map1.txt");

	return 0;
}


