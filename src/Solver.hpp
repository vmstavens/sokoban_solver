#pragma once

#include <fstream>
#include <vector>

#include "BreadthFirst.hpp"
#include "DepthFirst.hpp"

namespace ss
{
	class Solver
	{
	private:

	public:
		BreadthFirst breadthFirst;
		DepthFirst depthFirst;
		Solver();
		~Solver();
	};
	
	





}