#pragma once

#include <string>

class Position
{
private:

public:
	int y = 0;
	int x = 0;
	
	Position();
	Position(int x, int y);
	~Position();

	Position operator+(const Position& pos);
	Position operator-(const Position& pos);
	bool operator==(const Position& pos);
	bool operator!=(const Position& pos);
	Position operator+=(const Position& pos);
	Position operator-=(const Position& pos);
	Position operator*(int scale);

	std::string str();
};

