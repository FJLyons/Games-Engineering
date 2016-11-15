#pragma once

#include "GameObject.h"
#include "BasicTypes.h"

class Tile : public GameObject
{

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
	void Update(float deltaTime) override;

	Rect getRectangle();
	Colour getColour();
	Type getType();

	void setColour(int, int, int, int);

	void setSpawn();
	void setGoal();
	void setWall();

protected:
	Rect _rect;
	Colour _col;
	Type _type;
};
