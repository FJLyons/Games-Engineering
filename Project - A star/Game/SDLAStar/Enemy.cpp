#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy(Tile* tile)
{
	currentTile = tile;
	rect = tile->getRectangle();
}

Enemy::~Enemy()
{
}

void Enemy::Update(float dt)
{

}

Tile* Enemy::getNextTile(Tile* previousTile)
{
	return previousTile;
}

void Enemy::traverseTile(float dt)
{

}

void Enemy::Render(Renderer & r)
{
	r.drawRect(rect, Colour(255, 0, 0));
}


Rect Enemy::getRect()
{
	return rect;
}