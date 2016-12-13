#include "stdafx.h"
#include "Player.h"


Player::Player(Tile* tile)
{
	currentTile = tile;
	rect = tile->getRectangle();
}

Player::~Player()
{
}

void Player::Update(float dt)
{

}

Tile* Player::getNextTile(Tile* previousTile)
{
	return previousTile;
}

void Player::traverseTile(float dt)
{

}

void Player::Render(Renderer & r)
{
	r.drawRect(rect, Colour(0, 255, 0));
}


Rect Player::getRect()
{
	return rect;
}
