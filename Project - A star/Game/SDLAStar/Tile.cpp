#include "stdafx.h"
#include "Tile.h"


Tile::Tile(Rect r, Type t, int x, int y, int w)
	: _rect(r)
	, _type(t)
	, xPos(x)
	, yPos(y)
	, travelCost(w)
{
	switch (_type)
	{//set the colour based on its type
	case Type::PLAYER:
		_col = Colour(0, 255, 0, 255);
		break;
	case Type::ENEMY:
		_col = Colour(255, 0, 0, 255);
		break;
	case Type::WALL:
		_col = Colour(0, 0, 0, 255);
		travelCost = 100000;
		break;
	case Type::FLOORE:
		_col = Colour(255, 255, 255, 255);
		break;
	case Type::FLOORO:
		_col = Colour(200, 200, 200, 255);
		break;
	case Type::PATH:
		_col = Colour(125, 125, 255, 125);
		break;

	default:
		break;
	}
}

Tile::Tile(int x, int y)
	: xPos(x)
	, yPos(y)
{
	_type = Type::PATH;
	_col = Colour(125, 125, 255, 125);
}

Tile::~Tile()
{
}

void Tile::Render(Renderer& r)
{
	//draw
	r.drawWorldRect(_rect, _col);
}

void Tile::Update(float deltaTime)
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

void Tile::setPlayer()
{
	_type = Tile::Type::PLAYER;
	_col = Colour(0, 255, 0, 255);
}

void Tile::setEnemy()
{
	_type = Tile::Type::ENEMY;
	_col = Colour(255, 0, 0, 255);
}

void Tile::setWall()
{
	_type = Tile::Type::WALL;
	_col = Colour(0, 0, 0, 255);
	travelCost = 100000;
}

void Tile::setFloorE()
{
	_type = Tile::Type::FLOORE;
	_col = Colour(255, 255, 255, 255);
}

void Tile::setFloorO()
{
	_type = Tile::Type::FLOORO;
	_col = Colour(200, 200, 200, 255);
}

void Tile::setPath()
{
	_type = Tile::Type::PATH;
	_col = Colour(0, 0, 255, 255);
}