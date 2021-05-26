#include <iostream>

#include "Solver.hpp"


int main(int argc, char const *argv[])
{
	
	ss::Solver solver;

	solver.BreadthFirst.solve("maps/map1.txt");
	

	std::cout << "Hello, World" << std::endl;

	return 0;
}

