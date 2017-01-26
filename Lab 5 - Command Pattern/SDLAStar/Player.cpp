#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	rect = Rect(600, 600, 20, 20);
}

Player::~Player()
{
}

void Player::Update(float dt)
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

void Player::movePlayerUp()
{
	rect.pos.x = rect.pos.x;
	rect.pos.y = rect.pos.y - rect.size.h;
}

void Player::movePlayerLeft()
{
	rect.pos.x = rect.pos.x - rect.size.w;
	rect.pos.y = rect.pos.y;
}

void Player::movePlayerDown()
{
	rect.pos.x = rect.pos.x;
	rect.pos.y = rect.pos.y + rect.size.h;
}

void Player::movePlayerRight()
{
	rect.pos.x = rect.pos.x + rect.size.w;
	rect.pos.y = rect.pos.y;
}
