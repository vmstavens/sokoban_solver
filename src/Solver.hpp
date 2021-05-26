#include <fstream>
#include <vector>

#include "Algorithm.hpp"


namespace ss
{
	class Solver
	{
	private:
		Algorithm BreadthFirst;
		Algorithm DepthFirst;
		std::ifstream map;
		std::vector<std::string> map;

	public:
		Solver(std::ifstream map);
		~Solver();
	};
	
	





}