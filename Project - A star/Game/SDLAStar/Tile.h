#pragma once

#include "GameObject.h"
#include "BasicTypes.h"

class Tile : public GameObject
{
	Tile();
	~Tile();

public:
	//type to determine the type of block
	enum class Type
	{
		SPAWN,
		GOAL,
		FLOOR,
		PATH,
		WALL,
		OCCUPIED,
	};

	Tile(Rect r, Type t);
	~Tile();

	void Render(Renderer & r);
	void Update(unsigned int deltaTime);

	Rect getRectangle();
	Colour getColour();
	Type getType();

	void setColour(int, int, int, int);

protected:
	Rect _rect;
	Colour _col;
	Type _type;
};
