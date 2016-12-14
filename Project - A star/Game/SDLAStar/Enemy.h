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
	Enemy(Tile* tile, std::vector<std::vector<Tile*>> tiles);
	~Enemy();

	void Update(float dt);

	void Render(Renderer& r) override;
	Rect getRect();

	Tile* currentTile;
	std::vector<Tile*> currentPath;
	std::vector<std::vector<Tile*>> tileMap;


private:
	Rect rect;

	void moveEnemy(float dt);
	void setPosition(const Vector2f v);

	inline Vector2f lerp(float time, Vector2f a, Vector2f b)
	{
		if (time > 1.f)
			time = 1.f;
		return a * (1 - time) + b * time;
	}

	float elapsedTime = 0;
};

