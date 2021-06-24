#include <iostream>
#include <deque>

#include "BreadthFirst.hpp"
#include "Logger.hpp"
#include "Position.hpp"

std::vector<Position> BreadthFirst::m_cans_init = {};
std::vector<Position> BreadthFirst::m_goals_init = {};
Position BreadthFirst::m_robot_init;

// This method sets up the initial conditions for solve() to be executed.
void BreadthFirst::init(std::string path_to_map)
{
	LOGGER->Log("initial setup initiated...");

	std::vector<std::string> cl_map;
	Position robot_init;
	std::vector<Position> cans_init;
	std::vector<Position> goals_init;

	std::ifstream f_map(path_to_map);

	std::string map_line;
	if (f_map.is_open())
	{
		while (std::getline(f_map, map_line))
			cl_map.push_back(map_line);
		f_map.close();
		LOGGER->Log("map has been successfully created from file");
	}
	else
		LOGGER->Log("Unable to open map",Logger::LOG_TYPE::ERROR);

	for (size_t y = 0; y < cl_map.size(); y++)
	{
		for (size_t x = 0; x < cl_map[y].length(); x++)
		{
			if (cl_map[y][x] == 'R')
			{
				robot_init = Position(x, y);
				cl_map[y][x] = '.';
				continue;
			}
			if (cl_map[y][x] == 'G')
			{
				goals_init.push_back(Position(x, y));
				cl_map[y][x] = '.';
				continue;
			}
			if (cl_map[y][x] == 'C')
			{
				cans_init.push_back(Position(x, y));
				cl_map[y][x] = '.';
				continue;
			}
		}
	}
	this->m_cl_map = cl_map;
	this->m_cans_init = cans_init;
	this->m_robot_init = robot_init;
	this->m_goals_init = goals_init;

	LOGGER->Log("init done. The initial conditions are: ");
	LOGGER->Log("\tnumber of cans: \t" + std::to_string(this->m_cans_init.size()));
	LOGGER->Log("\trobot position: \t" + this->m_robot_init.str());
	LOGGER->Log("\tnumber of goals: \t" + std::to_string(this->m_goals_init.size()));
}

std::string BreadthFirst::solve(std::string path_to_map)
{
	/* algorithm BFS (Breadth First Search) : https://en.wikipedia.org/wiki/Breadth-first_search
	procedure BFS(G, root) is
	    let Q be a queue
	    label root as discovered
	    Q.enqueue(root)
	    while Q is not empty do
	        v := Q.dequeue()
	        if v is the goal then
	            return v
	        for all edges from v to w in G.adjacentEdges(v) do
	            if w is not labeled as discovered then
	                label w as discovered
	                Q.enqueue(w)
	*/
	
	init(path_to_map);

	LOGGER->Log("solution initiated on map " + path_to_map);

	// root node
	Node *init = new Node(this->m_cl_map, this->m_robot_init, this->m_cans_init, this->m_goals_init);

	LOGGER->Log("map layout loaded: ");
	init->logState();

	std::deque<Node *> node_queue;
	node_queue.push_back(init);
	Node *current_node;

	while (not node_queue.empty())
	{
		current_node = node_queue[0];

		if (current_node->isDone())
			return current_node->backtraceSolution();

		if (Node *up_node = current_node->move(Node::DIRECTION::UP); up_node != nullptr)
		{
			up_node->logState();
			up_node->m_parent = current_node;
			node_queue.push_back(up_node);
		}
		if (Node *down_node = current_node->move(Node::DIRECTION::DOWN); down_node != nullptr)
		{
			down_node->logState();
			down_node->m_parent = current_node;
			node_queue.push_back(down_node);
		}
		if (Node *left_node = current_node->move(Node::DIRECTION::LEFT); left_node != nullptr)
		{
			left_node->logState();
			left_node->m_parent = current_node;
			node_queue.push_back(left_node);
		}
		if (Node *right_node = current_node->move(Node::DIRECTION::RIGHT); right_node != nullptr)
		{
			right_node->logState();
			right_node->m_parent = current_node;
			node_queue.push_back(right_node);
		}

		node_queue.pop_front();
	}
	return "";
}