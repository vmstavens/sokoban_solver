#pragma once

#include <string>
#include <vector>

#include "Position.hpp"

class Node
{
private:
	std::string                     m_hash;
	Position                        m_robot;
	std::vector<Position>           m_cans;
	std::vector<Node*>              m_children;
	static std::vector<std::string> m_cl_map;
	static std::vector<Position>    m_goals;

	static std::vector<std::string> m_node_register; // this is used for keeping track of replicas.

public:
	Node*                           m_parent = nullptr;

	// to move the robot, these directions are provided.
	enum class DIRECTION { UP, DOWN, LEFT, RIGHT };

	Node();
	Node(Position robot);
	Node(Position robot, std::vector<Position> cans);
	Node(std::vector<std::string> cl_map, Position robot, std::vector<Position> cans,std::vector<Position> goals); // used for init
	~Node();

	void printState();
	void logState();

	std::vector<std::string> recreateMap();

	std::string getHash();
	std::string generateHash(Position robot, std::vector<Position> cans);

	std::string backtraceSolution();

	Node* move(DIRECTION dir);

	bool isFree(Position pos);
	bool isCan(Position pos);
	bool isCanMoveable(Position can);
	bool isReplica(Position new_robot_pos, std::vector<Position> new_cans);
	bool isDone();


};