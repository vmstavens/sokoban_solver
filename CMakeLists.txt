
cmake_minimum_required(VERSION 3.10)

project(sokoban_solver)

add_executable(sokoban_solver src/main.cpp src/Solver.cpp src/Algorithm.cpp src/Can.cpp src/Node.cpp src/Position.cpp src/Robot.cpp
	)


