#include <string>
#include <fstream>
#include <iostream>

#include "Algorithm.hpp"
#include "Logger.hpp"

std::vector<Position> Algorithm::m_cans_init = {};
std::vector<Position> Algorithm::m_goals_init = {};
Position Algorithm::m_robot_init;
std::vector<std::string> Algorithm::m_cl_map = {};

Algorithm::Algorithm()
{
}

Algorithm::Algorithm(std::ifstream f_map)
{

	// Here we need to initialize: m_cl_map, m_robot_init, m_cans_init and m_goals_init ////////////////////

	std::vector<std::string> cl_map;
	Position robot_init;
	std::vector<Position> cans_init;
	std::vector<Position> goals_init;


	std::string map_line;
	if (f_map.is_open())
	{
		while (std::getline(f_map, map_line))
			cl_map.push_back(map_line);
		f_map.close();
		LOGGER->Log("map has been created from file");
	}
	else
		std::cout << "Unable to open map";

	for (size_t y = 0; y < cl_map.size(); y++)
	{
		for (size_t x = 0; x < cl_map[y].length(); x++)
		{
			if (cl_map[y][x] == 'R')
			{
				robot_init = Position(x, y);
				cl_map[x][y] = '.';
				continue;
			}
			if (cl_map[y][x] == 'G')
			{
				goals_init.push_back(Position(x, y));
				cl_map[x][y] = '.';
				continue;
			}
			if (cl_map[y][x] == 'C')
			{
				cans_init.push_back(Position(x, y));
				cl_map[x][y] = '.';
				continue;
			}
		}
	}
	this->m_cl_map     = cl_map;
	this->m_cans_init  = cans_init;
	this->m_robot_init = robot_init;
	this->m_goals_init = goals_init;
}
Algorithm::~Algorithm() { }

std::string Algorithm::solve(std::string path_to_map) 
{ 
	std::cout << "Base class pure virtual function was called" << std::endl;
	return "Abstract solution"; 
}