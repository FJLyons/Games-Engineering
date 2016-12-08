#pragma once

#include "GameObject.h"
#include "BasicTypes.h"

class Tile : public GameObject
{

public:
	//type to determine the type of block
	enum class Type
	{
		PLAYER,
		ENEMY,
		WALL,
		FLOORE,
		FLOORO,
		PATH
	};

	Tile(Rect r, Type t, int x, int y);
	Tile(int x, int y);
	~Tile();

	void Render(Renderer & r);
	void Update(float deltaTime) override;

	Rect getRectangle();
	Colour getColour();
	Type getType();

	void setColour(int, int, int, int);

	void setPlayer();
	void setEnemy();
	void setWall();
	void setFloorE();
	void setFloorO();
	void setPath();

	int getSize();
	int amount = 0;

	int xPos, yPos;

protected:
	Rect _rect;
	Colour _col;
	Type _type;

public:
	int FunctionCost;
	int GraphCost;
	int HeuristicCost;

	Tile* parentTile;
};
