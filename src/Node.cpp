
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>

#include "Node.hpp"
#include "Logger.hpp"

std::vector<std::string> Node::m_cl_map;
std::vector<Position> Node::m_goals;
std::vector<std::string> Node::m_node_register;

Node::Node() { }

Node::Node(Position robot)
{
	this->m_robot = robot;
	this->m_hash = generateHash(robot, this->m_cans);
	this->m_node_register.push_back(this->getHash());
}

Node::Node(Position robot, std::vector<Position> cans)
{
	this->m_robot = robot;
	this->m_cans = cans;
	this->m_hash = generateHash(robot, cans);
	this->m_node_register.push_back(this->m_hash);
}

Node::Node(std::vector<std::string> cl_map, Position robot, std::vector<Position> cans, std::vector<Position> goals)
{
	this->m_cl_map = cl_map;
	this->m_robot  = robot;
	this->m_cans   = cans;
	this->m_goals  = goals;

	this->m_hash = generateHash(robot, cans);
	this->m_node_register.push_back(this->m_hash);
}

Node::~Node() { }

void Node::printState()
{
	std::vector<std::string> map = recreateMap();

	// print the map with the objects on it.
	for (const auto& line : map)
		std::cout << line << std::endl;
}

void Node::logState()
{
	std::vector<std::string> map = recreateMap();
	for (const auto& line : map)
	{
		LOGGER->Log("\t" + line, Logger::LOG_TYPE::INFO, false);
	}
	LOGGER->Log("", Logger::LOG_TYPE::INFO, false);
}

std::vector<std::string> Node::recreateMap()
{
	// go through cl_map, check each position, is position is equal to robot, goal or can, change char -> print map.
	std::vector<std::string> state_map = this->m_cl_map;

	// insert the positions of robot, cans and goals into a cl_map.
	for (size_t y = 0; y < state_map.size(); y++)
	{
		for (size_t x = 0; x < state_map[y].length(); x++)
		{
			if (std::find(m_goals.begin(), m_goals.end(), Position(x, y)) != m_goals.end())
				state_map[y][x] = 'G';
			if (Position(x, y) == m_robot)
				state_map[y][x] = 'R';
			if (std::find(m_cans.begin(), m_cans.end(), Position(x, y)) != m_cans.end())
				state_map[y][x] = 'C';
		}
	}
	return state_map;
}

std::string Node::getHash()
{
	std::string hash = "";
	hash += std::to_string(this->m_robot.x) + std::to_string(this->m_robot.y);
	for (const auto &c : this->m_cans)
		hash += std::to_string(c.x) + std::to_string(c.y);
	return hash;
}

std::string Node::generateHash(Position robot, std::vector<Position> cans)
{
	std::string hash = std::to_string(robot.x) + std::to_string(robot.y);
	for (const auto &c : cans)
		hash += std::to_string(c.x) + std::to_string(c.y);
	return hash;
}

std::string Node::backtraceSolution()
{
	LOGGER->Log("backtracing initiated...");

	Node* cn = this;

	std::string path = "";
	bool canIsPushed = false;
	
	while (cn->m_parent != nullptr)
	{
		bool canIsPushed = not std::is_permutation(cn->m_cans.begin(), cn->m_cans.end(), cn->m_parent->m_cans.begin());

		// left
		if ((cn->m_robot - cn->m_parent->m_robot) == Position(-1, 0))
		{
			if ( canIsPushed )
			{
				path += "L";
				cn = cn->m_parent;
				continue;
			}
			path += "l";
			cn = cn->m_parent;
			continue;
		}
		// right
		if ((cn->m_robot - cn->m_parent->m_robot) == Position(1, 0))
		{
			if ( canIsPushed )
			{
				path += "R";
				cn = cn->m_parent;
				continue;
			}
			path += "r";
			cn = cn->m_parent;
			continue;
		}
		// up
		if ((cn->m_robot - cn->m_parent->m_robot) == Position(0, -1))
		{
			if ( canIsPushed )
			{
				path += "U";
				cn = cn->m_parent;
				continue;
			}
			path += "u";
			cn = cn->m_parent;
			continue;
		}
		// down
		if ((cn->m_robot - cn->m_parent->m_robot) == Position(0, 1))
		{
			if ( canIsPushed )
			{
				path += "D";
				cn = cn->m_parent;
				continue;
			}
			path += "d";
			cn = cn->m_parent;
			continue;
		}
	}

	std::reverse(path.begin(),path.end());
	return path;
}

Node* Node::move(DIRECTION dir)
{
	Position dir_pos;

	switch (dir)
	{
	case DIRECTION::UP:
		dir_pos = Position(0,-1);
		LOGGER->Log("trying to move : UP");
		break;
	case DIRECTION::DOWN:
		dir_pos = Position(0,1);
		LOGGER->Log("trying to move : DOWN");
		break;
	case DIRECTION::LEFT:
		dir_pos = Position(-1,0);
		LOGGER->Log("trying to move : LEFT");
		break;
	case DIRECTION::RIGHT:
		dir_pos = Position(1,0);
		LOGGER->Log("trying to move : RIGHT");
		break;
	}

	Node* new_node         = nullptr;
	Position new_robot_pos = this->m_robot + dir_pos;


	// if nothing is in our way and the new state isn't a replica, move.
	if ( isFree(new_robot_pos) and not isReplica(new_robot_pos,this->m_cans) )
	{
		LOGGER->Log("the path is free and the state is not a replica...");
		new_node = new Node(new_robot_pos, this->m_cans);
		// new_node->m_node_register.push_back(new_node->getHash());
		return new_node;
	}
	// if a can is in out way, and it is moveable, move it.
	if (isCan(new_robot_pos) and isCanMoveable(new_robot_pos) )
	{
		LOGGER->Log("there is a can and it is moveable...");
		// a can is in our way, move it.
		for (size_t i = 0; i < this->m_cans.size(); i++)
		{
			// locate which can is in the way.
			if ( this->m_cans[i] == new_robot_pos )
			{
				std::vector<Position> new_node_cans = this->m_cans;

				new_node_cans[i]        = Position(new_node_cans[i] + dir_pos); // obs
				Position new_node_robot = this->m_robot + dir_pos;

				// is the new state a replica, if so, return nullptr
				if ( isReplica(new_node_robot, new_node_cans) )
					return nullptr;

				new_node = new Node(new_node_robot, new_node_cans);
				return new_node;
			}
		}
	}
	LOGGER->Log("it is not possible to move in this direction...\n");
	// it is not possible to move in this direction, and thus a nullptr is returned.
	return nullptr;
}

bool Node::isFree(Position pos)
{
	// Check for if a wall is in the given position pos
	if (this->m_cl_map[pos.y][pos.x] == '#')
		return false;
	
	// Check for if a can is in the given position pos
	for (const auto& c : this->m_cans)
	{
		if (pos == c)
			return false;
	}
	return true;
}

bool Node::isCan(Position pos)
{
	// Check for if a can is in the position given
	for (const auto &c : m_cans)
	{
		if (pos == c)
			return true;
	}
	return false;
}

bool Node::isCanMoveable(Position new_robot_pos)
{
	Position new_pos = this->m_robot + (new_robot_pos - this->m_robot) * 2; // p_new = p + 2*dp

	if ( isFree(new_pos) )
		return true;
	else
		return false;
}

bool Node::isReplica(Position new_robot_pos, std::vector<Position> new_cans)
{
	// if the node made from the input does not already exist in m_node_register
	if (std::find(m_node_register.begin(), m_node_register.end(), generateHash(new_robot_pos, new_cans)) != m_node_register.end())
		return true;
	else
		return false;
}

bool Node::isDone()
{	
	if (std::is_permutation(this->m_cans.begin(), this->m_cans.end(), this->m_goals.begin()))
	{
		LOGGER->Log("FINAL STATE:");
		this->logState();
	}
	return std::is_permutation(this->m_cans.begin(), this->m_cans.end(), this->m_goals.begin());
}

