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

	Tile(Rect r, Type t, int x, int y, int w);
	Tile(int x, int y);
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
	void setPath();

	// Node Functionality
	inline Tile& operator=(const Tile& target)
	{
		if (*this != target)
		{
			xPos = target.xPos;
			yPos = target.yPos;
			travelCost = target.travelCost;
		}

		return *this;
	}

	inline bool operator==(const Tile& target) const
	{
		return F == target.F && F == target.F;
	}

	inline bool operator!=(const Tile& target) const
	{
		return !(*this == target);
	}

	inline bool operator<(const Tile& target) const
	{
		return target.F < F;
	}

	int xPos, yPos;
	
	float travelCost;

protected:
	Rect _rect;
	Colour _col;
	Type _type;

public:
	int F;
	int G = 0;
	int H;

	Tile* parentTile;
};
