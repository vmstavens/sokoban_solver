#include <iostream>

#include "DepthFirst.hpp"
#include "Logger.hpp"
#include "Position.hpp"


DepthFirst::DepthFirst() { }

DepthFirst::~DepthFirst() { }

std::string DepthFirst::solve(std::string path_to_map)
{

	// Initiation ////////////////////////////////////////////////////
	/*
	+ Extract map
	+ Extract: Robot, cans, goals
	*/

	// Generate map member (std::vector<std::string>)
	std::string map_line;
	std::ifstream fmap(path_to_map);
	std::vector<std::string> map;

	if (fmap.is_open())
	{
		while (std::getline(fmap, map_line))
			map.push_back(map_line);
		fmap.close();
		LOGGER->Log("map has been created from file");
	}
	 else
		std::cout << "Unable to open map";
	
	Position robot;
	std::vector<Position> cans;
	std::vector<Position> goals;
	
	for (size_t y = 0; y < map.size(); y++)
	{
		for (size_t x = 0; x < map[y].length(); x++)
		{
			if (map[y][x] == 'R')
			{
				robot = Position(x, y);
				map[x][y] = '.';
				continue;
			}
			if (map[y][x] == 'G')
			{
				goals.push_back(Position(x, y));
				map[x][y] = '.';
				continue;
			}
			if (map[y][x] == 'C')
			{
				cans.push_back(Position(x, y));
				map[x][y] = '.';
				continue;
			}
		}
	
	// root node
	Node* init = new Node(map,robot,cans,goals);

	/*
	if (init.robot + up != wall or ) 

	if (init.down())

	if (init.left())

	if (init.right())
	
	*/

	return "done";
}
