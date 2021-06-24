#pragma once

#include "Algorithm.hpp"
#include "Logger.hpp"
// #include <deque>

class BreadthFirst : Algorithm
{
private:
	std::vector<std::string> m_cl_map;
	std::vector<Position> m_cans;
	std::vector<Position> m_goals;
	Position m_robot;

	static Position m_robot_init;
	static std::vector<Position> m_cans_init;
	static std::vector<Position> m_goals_init;
	static std::ifstream f_map;

public:
	BreadthFirst() : Algorithm() { };
	virtual ~BreadthFirst() {};

	void init(std::string path_to_map);

	virtual std::string solve(std::string path_to_map) override;

};

