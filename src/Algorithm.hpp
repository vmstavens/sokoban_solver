#pragma once
#include <string>

#include "Node.hpp"

class Algorithm
{
private:

public:
	Algorithm();
	Algorithm(std::ifstream map);
	~Algorithm();

	virtual std::string solve(std::string path_to_map);
};
