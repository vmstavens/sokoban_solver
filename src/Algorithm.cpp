#include <string>
#include <fstream>
#include <iostream>
#include <cctype>
#include <cstring>
#include <map>

#include "Algorithm.hpp"
#include "Logger.hpp"


Algorithm::Algorithm() { }

Algorithm::~Algorithm() { }

std::string Algorithm::abs2relSolution(std::string abs_solution)
{

	/* Translate up, down, left, right into turn left, turn right, forward, turn around and push
	
	ABSOLUTE DIRECTIONS:
	 + u = UP
	 + d = DOWN
	 + l = LEFT
	 + r = RIGHT

	RELATIVE DIRECTIONS
	+ f = FORWARD
	+ l = TURN LEFT
	+ r = TURN RIGHT
	+ u = MAKE A U-TURN
	
	*/

	std::map<char,int> dir_map = 
	{
		{'u',1},
		{'r',2},
		{'d',3},
		{'l',4},
	};

	char look_dir       = 'u';
	std::string rel_sol = "";

	for (const auto& dir : abs_solution)
	{
		int d_turn        = (dir_map.find(look_dir)->second - dir_map.find( tolower(dir) )->second);

		bool isPushing    = isupper(dir);
		bool goingForward = d_turn == 0 ? true : false;
		bool goingRight   = d_turn == -1 or d_turn == 3 ? true : false;
		bool goingLeft    = d_turn == 1 or d_turn == -3 ? true : false;
		bool UTurning     = d_turn == 2 ? true : false;

		if (goingLeft)
		{
			rel_sol += "l";
			look_dir = dir;
		}

		if (goingRight)
		{
			rel_sol += "r";
			look_dir = dir;
		}

		if (UTurning)
		{
			rel_sol += "u";
			look_dir = dir;
		}

		if (isPushing)
		{
			rel_sol += "p";
			continue;
		}

		rel_sol += "f";

	}

	return rel_sol;
}

std::string Algorithm::optimizeSolution(std::string non_optimized_solution)
{
	// Optimized solution
	/*
	We convert the relative solution from its original form to an optimized 
	version.

	OPTIMIZATION
	 + repetitions of actions are reduced into the action times the number of repetitions.
	 + Ex. fflfflrfff -> 2fl2flr3f
	*/

	std::string result = "";
	int rep_count = 0;

	// Going through string
	for (size_t i = 0; i < non_optimized_solution.length(); i++)
	{
		bool isRepeated = false;
		char current_char = non_optimized_solution[i];

		// if the next char is equal to the current, we have a repetition, how many reps to we have?
		if (current_char == non_optimized_solution[i + 1])
			isRepeated = true;

		// Calculating the numbers of reps
		if (isRepeated)
		{
			for (size_t j = i; j < non_optimized_solution.length(); j++)
			{
				if (current_char == non_optimized_solution[j + 1])
					rep_count++;
				else
				{
					i = j;
					break;
				}
			}
		}
		if (isRepeated)
			result += std::to_string(rep_count + 1) + current_char;
		else
			result += current_char;

		rep_count = 0;
	}

	return result;
}