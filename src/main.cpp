#include <iostream>

#include "Solver.hpp"
#include "Logger.hpp"

int main(int argc, char const *argv[])
{

	LOGGER->clear();

	ss::Solver solver;

	LOGGER->Log("solving with BF...");
	solver.breadthFirst.solve("maps/harder_map.txt");

	return 0;
}


