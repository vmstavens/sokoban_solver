#include "Solver.hpp"

Solver::Solver(std::ifstream map)
{

	this->map = map;

	std::stirng line;

	while (std::getline(map, line))
		this->map.push_back(line);
}

Solver::~Solver()
{
}
