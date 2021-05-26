#include <string>
#include <fstream>

#include "Algorithm.hpp"

Algorithm::Algorithm() { }

Algorithm::Algorithm(std::ifstream map)
{ 
	std::string line;
	while (std::getline(map, line))
		this->m_map.push_back(line);
}

Algorithm::~Algorithm() { }

std::string solve(std::string path_to_map)
{
	
}