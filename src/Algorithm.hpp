#pragma once
#include <string>

#include "Node.hpp"

class Algorithm
{
private:
	static Position m_robot_init;
	static std::vector<Position> m_cans_init;
	static std::vector<Position> m_goals_init;
	static std::vector<std::string> m_cl_map;

public:
	Algorithm();
	Algorithm(std::ifstream f_map);
	~Algorithm();

	virtual std::string solve(std::string path_to_map) = 0;
};
