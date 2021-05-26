#include "Position.hpp"

Position::Position() { }

Position::Position(int x = 0, int y = 0)
{
	this->x = x;
	this->y = y;
}

Position::~Position() {}

Position Position::operator+(const Position& pos)
{
	return Position(this->x + pos.x, this->y + pos.y);
}

Position Position::operator-(const Position& pos)
{
	return Position(this->x - pos.x, this->y - pos.y);
}
