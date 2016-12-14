#include "stdafx.h"
#include "Player.h"


Player::Player(Tile* tile, std::vector<std::vector<Tile*>> tiles)
{
	currentTile = tile;
	rect = tile->getRectangle();
	tileMap = tiles;

	if (tileMap[currentTile->xPos][currentTile->yPos]->getType() == Tile::Type::WALL)
	{
		currentTile = tileMap[currentTile->xPos + 1][currentTile->yPos];
	}
}

Player::~Player()
{
}

void Player::Update(float dt)
{
	elapsedTime += dt;
	if(elapsedTime >= 1)
		movePlayer(dt);
}

void Player::Render(Renderer & r)
{
	r.drawRect(rect, Colour(0, 255, 0));
}

Rect Player::getRect()
{
	return rect;
}

void Player::movePlayer(float dt)
{
	Point2D newPosition = rect.pos;
	int direction = rand() % 4 + 1;
	if (direction == 1) // Right
	{ 
		if (tileMap[currentTile->xPos + 1][currentTile->yPos]->getType() != Tile::Type::WALL
			&& currentTile->xPos < tileMap.size() - 2)
		{
			currentTile = tileMap[currentTile->xPos + 1][currentTile->yPos];
			rect = currentTile->getRectangle();
			newPosition.x = rect.pos.x + rect.size.w;
			newPosition.y = rect.pos.y;
		}
	}
	if (direction == 2)  // Down
	{
		if (tileMap[currentTile->xPos][currentTile->yPos + 1]->getType() != Tile::Type::WALL
			&& currentTile->yPos < tileMap[0].size() - 2)
		{
			currentTile = tileMap[currentTile->xPos][currentTile->yPos + 1];
			rect = currentTile->getRectangle();

			newPosition.x = rect.pos.x;
			newPosition.y = rect.pos.y + rect.size.h;
		}
	}
	if (direction == 3) // Left
	{ 
		if (tileMap[currentTile->xPos - 1][currentTile->yPos]->getType() != Tile::Type::WALL
			&& currentTile->xPos > 1)
		{
			currentTile = tileMap[currentTile->xPos - 1][currentTile->yPos];
			rect = currentTile->getRectangle();

			newPosition.x = rect.pos.x - rect.size.w;
			newPosition.y = rect.pos.y;
		}
	}
	if (direction == 4) // Up
	{
		if (tileMap[currentTile->xPos][currentTile->yPos - 1]->getType() != Tile::Type::WALL
			&& currentTile->yPos > 1)
		{
			currentTile = tileMap[currentTile->xPos][currentTile->yPos - 1];
			rect = currentTile->getRectangle();

			newPosition.x = rect.pos.x;
			newPosition.y = rect.pos.y - rect.size.h;
		}
	}

	setPosition(lerp(elapsedTime /100, Vector2f(rect.pos.x, rect.pos.y), Vector2f(newPosition.x, newPosition.y)));
	elapsedTime = 0;
}

void Player::setPosition(const Vector2f v)
{
	rect.pos.x = v.x;
	rect.pos.y = v.y;
}
