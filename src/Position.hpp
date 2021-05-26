#pragma once

class Position
{
private:
	int x = 0;
	int y = 0;

public:
	Position();
	Position(int x, int y);
	~Position();

	Position operator+(const Position& pos);
	Position operator-(const Position& pos);
};

