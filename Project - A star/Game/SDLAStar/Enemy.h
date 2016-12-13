#pragma once

#include "GameObject.h"
#include "BasicTypes.h"
#include "Tile.h"
#include "Threading.h"
#include "Pathfinder.h"

#include <vector>

#include "Player.h"


class Enemy : public GameObject
{
public:
	Enemy(Tile* tile);
	~Enemy();

	void Update(float dt);

	void Render(Renderer& r) override;
	Rect getRect();

	std::vector<Tile*> currentPath;

	Tile* currentTile;

private:

	Tile* getNextTile(Tile* previousTile);
	void traverseTile(float dt);

	Rect rect;
};

