#include <string>
#include <vector>

#include "Node.hpp"

class Algorithm
{
private:
	std::vector<std::string> m_map;
	Node* node = nullptr;

public:
	Algorithm();
	Algorithm(std::ifstream map);
	
	~Algorithm();

	std::string solve(std::string path_to_map);
};
