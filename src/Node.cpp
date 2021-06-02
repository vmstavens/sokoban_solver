
#include <algorithm>

#include "Node.hpp"

std::vector<std::string> Node::m_cl_map;
std::vector<Position> Node::m_goals;

Node::Node() { }

Node::Node(Position robot, std::vector<Position> cans)
{
	this->m_robot = robot;
	this->m_cans = cans;
}

Node::Node(Position robot)
{
	this->m_robot = robot;
}

Node::Node(std::vector<std::string> cl_map, Position robot, std::vector<Position> cans, std::vector<Position> goals)
{
	this->m_cl_map = cl_map;
	this->m_robot  = robot;
	this->m_cans   = cans;
	this->m_goals  = goals;
}

Node::~Node() { }

Node* Node::move(DIRECTION dir)
{

	Position dir_pos;

	switch (dir)
	{
	case DIRECTION::UP:
		dir_pos = Position(0,1);
		break;
	case DIRECTION::DOWN:
		dir_pos = Position(0,-1);
		break;
	case DIRECTION::LEFT:
		dir_pos = Position(-1,0);
		break;
	case DIRECTION::RIGHT:
		dir_pos = Position(1,0);
		break;
	}

	Node* dir_node = nullptr;

	// if nothing is in our way upwards, move.
	if (isFree(this->m_robot + dir_pos))
	{
		dir_node = new Node(Position(this->m_robot + dir_pos));
		return dir_node;
	}
	// if a can is in out way, and its moveable, move it.
	else if (isCan(this->m_robot + dir_pos) and isCanMoveable(this->m_robot + dir_pos))
	{
		// a can is in our way, move it.
		for (size_t i = 0; i < this->m_cans.size(); i++)
		{
			// locate the can which is in the way.
			if (this->m_cans[i] == (this->m_robot + dir_pos))
			{
				std::vector<Position> dir_node_cans = this->m_cans;
				dir_node_cans[i]                    = Position(this->m_robot + dir_pos);
				Position dir_node_robot             = this->m_robot + dir_pos;
				dir_node                            = new Node(dir_node_robot, dir_node_cans);
				return dir_node;
			}
		}
	}
	// it is not possible to move in this direction, and thus a nullptr is returned.
	else
		return nullptr;
}

bool Node::isFree(Position pos)
{
	// Check for if a wall is in the given position pos
	if (this->m_cl_map[pos.x][pos.y] == '#')
		return false;
	
	// Check for if a can is in the given position pos
	for (const auto& c : m_cans)
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

bool Node::isCanMoveable(Position can)
{
	Position new_pos = this->m_robot + (can - this->m_robot) * 2; // p_new = p + 2*dp
	if ( isFree(new_pos) )
		return true;
	else
		return false;
}

bool Node::isDone()
{
	for (const auto& c : this->m_cans)
	{
		if (std::find(this->m_goals.begin(), this->m_goals.end(), c) != this->m_goals.end());
			return false;
	}
	return true;
}

