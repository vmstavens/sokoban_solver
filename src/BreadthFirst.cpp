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
	LOGGER->Log("solution initiated...");
	// root node
	Node* init = new Node(this->m_cl_map, this->m_robot_init, this->m_cans_init, this->m_goals_init);

	std::deque<Node*> node_queue;
	node_queue.push_back(init);
	Node* current_node;

	size_t layer_counter = 0;

	while (not node_queue.empty())
	{

		LOGGER->Log("Layer counter: " + std::to_string(layer_counter));

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
	return "done";
}