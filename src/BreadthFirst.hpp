
#include "Algorithm.hpp"

class BreadthFirst : Algorithm
{
private:
	std::vector<std::string> m_cl_map;
	std::vector<Position> m_cans_init;
	std::vector<Position> m_goals_init;
	Position m_robot_init;
public:
	BreadthFirst() : Algorithm() {};
	~BreadthFirst() {};

	inline std::string solve(std::string path_to_map) override { return "Hello!"; };
};

