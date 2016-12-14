#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy(Tile* tile, std::vector<std::vector<Tile*>> tiles)
{
	currentTile = tile;
	rect = tile->getRectangle();
	tileMap = tiles;

	if (tileMap[currentTile->xPos][currentTile->yPos]->getType() == Tile::Type::WALL)
	{
		currentTile = tileMap[currentTile->xPos + 1][currentTile->yPos];
	}
}

Enemy::~Enemy()
{
}

void Enemy::Update(float dt)
{
	elapsedTime += dt;

	if (tileMap.size() == 30)
	{
		if (elapsedTime >= 0.1f)
		{
			moveEnemy(dt);
		}
	}

	if (tileMap.size() == 100)
	{
		if (elapsedTime >= 0.01f)
		{
			moveEnemy(dt);
		}
	}

	else
	{
		moveEnemy(dt);
	}
}

void Enemy::Render(Renderer & r)
{
	r.drawRect(rect, Colour(255, 0, 0));
}


Rect Enemy::getRect()
{
	return rect;
}


void Enemy::moveEnemy(float dt)
{
	Point2D newPosition = rect.pos;

	if (!currentPath.empty())
	{
		currentTile = tileMap[currentPath[currentPath.size() - 1]->xPos][currentPath[currentPath.size() - 1]->yPos];
		currentPath.pop_back();
		rect = currentTile->getRectangle();
		newPosition.x = rect.pos.x;
		newPosition.y = rect.pos.y;
		if(currentPath.empty())
			hasFinished = true;
	}
	else if(needsToSearch == false && hasFinished == true)
	{
		needsToSearch = true;
	}


	setPosition(lerp(elapsedTime / 100, Vector2f(rect.pos.x, rect.pos.y), Vector2f(newPosition.x, newPosition.y)));
	elapsedTime = 0;
}

void Enemy::setPosition(const Vector2f v)
{
	rect.pos.x = v.x;
	rect.pos.y = v.y;
}