
#include <string>
#include <vector>

#include "Robot.hpp"
#include "Can.hpp"


class Node
{
private:
	std::string      hash;
	Robot            robot;
	std::vector<Can> cans;
public:
	Node();
	~Node();
};

