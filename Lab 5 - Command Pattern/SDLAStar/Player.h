#pragma once
#include "GameObject.h"
#include "BasicTypes.h"

#include <vector>


class Player : GameObject
{
public:
	//Player(std::vector<Tile*> path);
	Player();
	Player::~Player();

	void Update(float dt);

	void Render(Renderer& r) override;
	Rect getRect();


	void movePlayerUp();
	void movePlayerLeft();
	void movePlayerDown();
	void movePlayerRight();

private:
	Rect rect;

	float elapsedTime = 0;
};
