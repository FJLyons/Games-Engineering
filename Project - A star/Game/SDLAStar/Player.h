#pragma once
#include "GameObject.h"
#include "BasicTypes.h"

#include "Tile.h"

#include <vector>


class Player : GameObject
{
public:
	//Player(std::vector<Tile*> path);
	Player(Tile* tile);
	Player::~Player();

	void Update(float dt);

	void Render(Renderer& r) override;
	Rect getRect();

	Tile* currentTile;

private:

	Tile* getNextTile(Tile* previousTile);
	void traverseTile(float dt);

	Rect rect;
};
