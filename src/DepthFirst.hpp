
#include "Algorithm.hpp"

class DepthFirst : Algorithm
{
private:
	/* data */
public:
	DepthFirst() : Algorithm() {};
	~DepthFirst() {};

	inline std::string solve(std::string path_to_map) override {return "Hello2!";};
};

