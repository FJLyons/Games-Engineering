#pragma once
#include "GameObject.h"
#include "BasicTypes.h"

#include "Tile.h"

#include <vector>


class Player : GameObject
{
public:
	//Player(std::vector<Tile*> path);
	Player(Tile* tile, std::vector<std::vector<Tile*>> tiles);
	Player::~Player();

	void Update(float dt);

	void Render(Renderer& r) override;
	Rect getRect();

	Tile* currentTile;
	std::vector<std::vector<Tile*>> tileMap;

private:
	Rect rect;

	void movePlayer(float dt);
	void setPosition(const Vector2f v);

	inline Vector2f lerp(float time, Vector2f a, Vector2f b)
	{
		if (time > 1.f)
			time = 1.f;
		return a * (1 - time) + b * time;
	}

	float elapsedTime = 0;
};
