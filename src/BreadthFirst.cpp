#include <iostream>
#include <deque>

#include "BreadthFirst.hpp"
#include "Logger.hpp"
#include "Position.hpp"

BreadthFirst::BreadthFirst() { }

BreadthFirst::~BreadthFirst() { }

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
		Node* init = new Node(map, robot, cans, goals);

		std::deque<Node*> node_queue;
		node_queue.push_back(init);
		Node* current_node;
		std::vector<Node*> node_children;

		while (not node_queue.empty())
		{
			current_node = node_queue[0];
			node_queue.pop_front();

			if ( current_node->isDone() )
				return "done"; // CHANGE

			if (Node* up_node = current_node->move(Node::DIRECTION::UP); up_node != nullptr)
				node_queue.push_back(up_node);
			if (Node* down_node = current_node->move(Node::DIRECTION::DOWN); down_node != nullptr)
				node_queue.push_back(down_node);
			if (Node* left_node = current_node->move(Node::DIRECTION::LEFT); left_node != nullptr)
				node_queue.push_back(left_node);
			if (Node* right_node = current_node->move(Node::DIRECTION::RIGHT); right_node != nullptr)
				node_queue.push_back(right_node);
		}

		/*
		Notes:
		+ clean map? where do we construct it to be most efficient?
		*/
		return "done";
	}