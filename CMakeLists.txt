
cmake_minimum_required(VERSION 3.10)

project(project)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ADDITIONAL_CFLAGS} -g")

add_executable(project 
	src/main.cpp 
	src/Solver.cpp 
	src/Algorithm.cpp 
	src/Node.cpp 
	src/Position.cpp 
	src/Logger.cpp 
	src/BreadthFirst.cpp 
	src/DepthFirst.cpp )


