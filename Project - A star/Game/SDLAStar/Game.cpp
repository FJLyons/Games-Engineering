#include "stdafx.h"

#include <iostream>
using namespace std;
#include <chrono>
#include <thread>

#include "LTimer.h"
#include "Game.h"
#include "SceneManager.h"
#include "LevelLoader.h"

const int SCREEN_FPS = 10;
const int SCREEN_TICKS_PER_FRAME = 100;

Game::Game()
{
	quit = false;
	pathfinder = new Pathfinder();
}

Game::~Game()
{
}

bool Game::init(int levelNumber) {	
	// Set Window Size
	Size2D winSize(2000,2000);

	// Objects
	tiles = LevelLoader::instance()->LoadLevel(levelNumber);

	// Set Up Each Level
	if (levelNumber == 0)
	{
		scale = 30.0f/30.0f;
		levelSize = 30;

		endTile = tiles[rand() % 10][rand() % 10 + 10];
		player = new Player(endTile, tiles);
		for (int i = 0; i < 1; i++)
		{
			startTile = tiles[rand() % 10 + 20][rand() % 10 + 10];
			enemies.push_back(new Enemy(startTile, tiles));
		}
	}
	else if (levelNumber == 1)
	{
		scale = 100.0f/30.0f;
		levelSize = 100;

		endTile = tiles[rand() % 33][rand() % 33 + 33];
		player = new Player(endTile, tiles);
		for (int i = 0; i < 1; i++)
		{
			startTile = tiles[rand() % 33 + 66][rand() % 33 + 33];
			enemies.push_back(new Enemy(startTile, tiles));
		}
	}
	else if (levelNumber == 2)
	{
		scale = 1000.0f/30.0f;
		levelSize = 1000;

		endTile = tiles[rand() % 333][rand() % 333 + 333];
		player = new Player(endTile, tiles);
		for (int i = 0; i < 1; i++)
		{
			startTile = tiles[rand() % 333 + 666][rand() % 333 + 333];
			enemies.push_back(new Enemy(startTile, tiles));
		}
	}
	else
	{
		startTile = tiles[0][0];
		endTile = tiles[19][19];
	}

	// Camera
	camera = new Camera2D(Rect(0, 0, winSize.w, winSize.h), scale);
	camera->setLevelSize(Size2D(winSize.w, winSize.h));
	renderer.setNewCamera(camera);

	// A Star
	//pathfinder->Find(startTile, endTile, tiles);
	Threading::getInstance()->spawnWorkers();
	for (int i = 0; i < enemies.size(); i++)
	{
		Threading::getInstance()->addTask(std::bind( // Bind function for threading
			&Pathfinder::Find, // Function to bind
			pathfinder, // Class object for function
			enemies[i]->currentTile, // Start position for A star
			player->currentTile, // End position for A star
			tiles // tile map
		));
	}

	// Time
	lastTime = LTimer::gameTime();
	
	// Events
	inputManager.AddListener(EventListener::Event::QUIT, this);
	inputManager.AddListener(EventListener::Event::SPACE, this);
	inputManager.AddListener(EventListener::Event::ANYKEY, this);
	inputManager.AddListener(EventListener::Event::UP, this);
	inputManager.AddListener(EventListener::Event::DOWN, this);
	inputManager.AddListener(EventListener::Event::LEFT, this);
	inputManager.AddListener(EventListener::Event::RIGHT, this);
	inputManager.AddListener(EventListener::Event::ZOOM_IN, this);
	inputManager.AddListener(EventListener::Event::ZOOM_OUT, this);

	// Bools
	quit = false;
	progress = false;

	//creates our renderer, which looks after drawing and the window
	renderer.init(winSize, "A Star Threading", camera);

	return true;
}

void Game::update()
{
	unsigned int currentTime = LTimer::gameTime();//millis since game started
	float deltaTime = (currentTime - lastTime) / 1000.0;//time since last update

	//save the curent time for next frame
	lastTime = currentTime;

	//for (auto& enemy : enemies)
	//{
	//	enemy->Update(deltaTime);
	//}

	player->Update(deltaTime);
}

void Game::render()
{
	renderer.clear(Colour(0,0,0));// prepare for new frame

	// Culling
	int tilesDrawn = 0;
	Rect camPos = (camera->getViewport() / camera->getScale());
	int maxColumn = (camPos.pos.x + camPos.size.w) / tiles[0][0]->getSize();
	int maxRow = (camPos.pos.y + camPos.size.h) / tiles[0][0]->getSize();

	for (int column = camPos.pos.x / tiles[0][0]->getSize(); column <= maxColumn; column++)
	{
		for (int row = camPos.pos.y / tiles[0][0]->getSize(); row <= maxRow; row++)
		{
			if (row < levelSize && column < levelSize && row >= 0 && column >= 0)
			{
				tiles.at(column).at(row)->Render(renderer);
				tilesDrawn++;
			}
		}
	}

	for (auto& enemy : enemies)
	{
		if (camPos.containsPoint(enemy->getRect().pos))
		{
			enemy->Render(renderer);
		}
	}

	if (camPos.containsPoint(player->getRect().pos))
	{
		player->Render(renderer);
	}

	//cout << "Tiles drawn = " << tilesDrawn << endl;

	renderer.present();// display the new frame (swap buffers)
}

void Game::loop()
{
	LTimer capTimer; // cap framerate

	while (!quit) 
	{ 
		//game loop
		capTimer.start();

		inputManager.ProcessInput(false);

		update();
		render();

		if (progress == true)
		{
			for (std::vector< std::vector<Tile*> >::iterator it = tiles.begin(); it != tiles.end(); ++it)
			{
				for (std::vector< Tile*>::iterator it2 = (*it).begin(); it2 != (*it).end(); ++it2)
				{
					delete *it2;
				}
				(*it).clear();
			}
			tiles.clear();
			tiles.shrink_to_fit();
			break;
		}

		int frameTicks = capTimer.getTicks();//time since start of frame
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			//Wait remaining time before going to next frame
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}
	}
}

// Event manager
void Game::onEvent(EventListener::Event evt)
{
	switch (evt)
	{
	case (EventListener::Event::QUIT):
		SceneManager::instance()->destroy();
		break;
	case (EventListener::Event::SPACE):
		progress = true;
		break;
	case (EventListener::Event::ANYKEY):
		break;
	case(EventListener::Event::LEFT):
		camera->MoveLeft();
		break;
	case(EventListener::Event::RIGHT):
		camera->MoveRight();
		break;
	case(EventListener::Event::UP):
		camera->MoveUp();
		break;
	case(EventListener::Event::DOWN):
		camera->MoveDown();
		break;
	case(EventListener::Event::ZOOM_IN):
		camera->scaleUp();
		break;
	case(EventListener::Event::ZOOM_OUT):
		camera->scaleDown();
		break;
	}
}

// Close app
void Game::destroy()
{
	for (std::vector< std::vector<Tile*> >::iterator it = tiles.begin(); it != tiles.end(); ++it)
	{
		for (std::vector< Tile*>::iterator it2 = (*it).begin(); it2 != (*it).end(); ++it2)
		{
			delete *it2;
		}
		(*it).clear();
	}
	tiles.clear();
	tiles.shrink_to_fit();

	for (std::vector< Enemy* >::iterator it = enemies.begin(); it != enemies.end(); ++it)
	{
		delete *it;
	}
	enemies.clear();
	enemies.shrink_to_fit();

	delete player;


	renderer.destroy();
}