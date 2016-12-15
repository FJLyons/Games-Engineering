#pragma once

#include <vector>

#include "Renderer.h"
#include "GameObject.h"
#include "EventListener.h"
#include "InputManager.h"
#include "Tile.h"

#include "Pathfinder.h"

#include "Camera2D.h"

#include "Threading.h"

#include "Enemy.h"
#include "Player.h"


/** The game objct whic manages the game loop*/
class Game:public EventListener
{
	InputManager inputManager;
	Renderer renderer;

	std::vector<std::vector<Tile*>> tiles;
	Tile* startTile; // enemy
	Tile* endTile; // player
	std::vector<Tile*> wayPoints;


	vector<Tile*> waypoints;
	vector<Enemy*> enemies;
	vector<Enemy*> enemiesToDelete;
	Player * player;

	Camera2D * camera;
	float scale;
	int levelSize;

	Pathfinder* pathfinder; // A Star

	// Variables
	unsigned int lastTime; // time of last update;

	bool progress; // Move to next level
	bool quit; // quit app

	bool threaded = false;

public:
	Game();
	~Game();

	bool init(int levelNumber, Renderer rend, Camera2D* cam);
	void update();
	void render();
	void loop();

	void destroy();
	void onEvent(EventListener::Event);

	//struct CompareTiles
	//{
	//	bool operator() (Tile* lhs, Tile* rhs)
	//	{
	//		return lhs->getIndexPosition() < rhs->getIndexPosition();
	//	}
	//};
};

