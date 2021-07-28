#pragma once

#include "Algorithm.hpp"

class DepthFirst : Algorithm
{
private:
	/* data */
public:
	DepthFirst() : Algorithm() {};
	virtual ~DepthFirst() {};

	virtual std::string solve(std::string path_to_map) override;
};

