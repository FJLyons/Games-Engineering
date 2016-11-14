#include "stdafx.h"
#include "Tile.h"


Tile::Tile(Rect r, Type t)
	: _rect(r)
	, _type(t)
{
	switch (_type)
	{//set the colour based on its type
	case Type::SPAWN:
		_col = Colour(255, 125, 125, 125);
		break;
	case Type::GOAL:
		_col = Colour(125, 255, 125, 125);
		break;
	case Type::PATH:
		_col = Colour(125, 125, 255, 125);
	case Type::FLOOR:
		_col = Colour(255, 255, 255, 255);
		break;
	case Type::WALL:
		_col = Colour(0, 0, 0, 255);
		break;
	case Type::OCCUPIED:
		_col = Colour(0, 0, 255, 255);
		break;
	default:
		break;
	}
}


Tile::~Tile()
{
}

void Tile::Render(Renderer& r)
{
	//draw
	r.drawWorldRect(_rect, _col);
}

void Tile::Update(unsigned int deltaTime)
{
	//do nothing
}

Rect Tile::getRectangle()
{
	return _rect;
}
Colour Tile::getColour()
{
	return _col;
}
Tile::Type Tile::getType()
{
	return _type;
}

void Tile::setColour(int r, int g, int b, int a)
{
	_col = Colour(r, g, b, a);
}