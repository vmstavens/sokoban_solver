#pragma once
#include <string>

#include "Node.hpp"

class Algorithm
{
private:
	

public:

	Algorithm();
	virtual ~Algorithm();

	virtual std::string solve(std::string path_to_map) = 0;
	void setMap(std::string str_map);
};
