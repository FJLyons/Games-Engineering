#include "stdafx.h"

#include <iostream>
using namespace std;



#include "LTimer.h"
#include "Game.h"
#include "SceneManager.h"
#include "LevelLoader.h"


const int SCREEN_FPS = 100000;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;


Game::Game()
{
	pause = false;
	quit = false;
}


Game::~Game()
{
}


bool Game::init(int levelNumber) {	
	Size2D winSize(2000,2000);

	//set up the viewport
	Size2D vpSize(2000, 2000);
	Point2D vpBottomLeft(0, 0);

	Rect vpRect(vpBottomLeft, vpSize);
	renderer.setViewPort(vpRect);

	// Objects
	tiles = LevelLoader::instance()->LoadLevel(levelNumber);

	if (levelNumber == 1)
	{
		startTile = tiles[0][0];
		endTile = tiles[19][19];
		scale = 1;
	}
	else if (levelNumber == 2)
	{
		startTile = tiles[0][0];
		endTile = tiles[99][99];
		scale = 3;
	}
	else if (levelNumber == 3)
	{
		startTile = tiles[0][0];
		endTile = tiles[999][999];
		scale = 30;
	}
	else
	{
		startTile = tiles[0][0];
		endTile = tiles[19][19];
	}

	// A Star
	pathfinder->Find(startTile, endTile, tiles);

	// Camera
	camera = new Camera2D(Rect(0, 0, winSize.w, winSize.h), scale);
	camera->setLevelSize(Size2D(winSize.w, winSize.h));
	renderer.setNewCamera(camera);

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
	progress = false;


	//creates our renderer, which looks after drawing and the window
	renderer.init(winSize, "A Star Threading", camera);

	return true;
}


void Game::destroy()
{
	//empty out the game object vector before quitting
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles.size(); j++)
		{
			delete tiles.at(i).at(j);
		}
	}

	tiles.clear();
	renderer.destroy();
}

//** calls update on all game entities*/
void Game::update()
{
	unsigned int currentTime = LTimer::gameTime();//millis since game started
	float deltaTime = (currentTime - lastTime) / 1000.0;//time since last update

	//call update on all game objects
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles.size(); j++)
		{
			tiles.at(i).at(j)->Update(deltaTime);
		}
	}

	//save the curent time for next frame
	lastTime = currentTime;
}

//** calls render on all game entities*/

void Game::render()
{
	renderer.clear(Colour(0,0,0));// prepare for new frame
	
	////render every object
	//for (int i = 0; i < tiles.size(); i++)
	//{
	//	for (int j = 0; j < tiles.size(); j++)
	//	{
	//		tiles.at(i).at(j)->Render(renderer);
	//	}
	//}

	Rect camPos = (camera->getViewport() / camera->getScale());
	int maxColumn = (camPos.pos.x + camPos.size.w) / 30;
	int maxRow = (camPos.pos.y + camPos.size.h) / 30;
	for (int column = camPos.pos.x / 30; column <= maxColumn; column++)
	{
		for (int row = camPos.pos.y / 30; row <= maxRow; row++)
		{
			if (row < 30 && column < 30 && row >= 0 && column >= 0)
			{
				tiles.at(column).at(row)->Render(renderer);
			}
		}
	}

	renderer.present();// display the new frame (swap buffers)
}

/** update and render game entities*/
void Game::loop()
{
	LTimer capTimer;//to cap framerate

	int frameNum = 0;
	while (!quit) { //game loop
		capTimer.start();

		inputManager.ProcessInput(false);

		if (progress == true)
		{
			break;
		}

		//if(!pause) //in pause mode don't bother updateing
			update();
		render();

		int frameTicks = capTimer.getTicks();//time since start of frame
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			//Wait remaining time before going to next frame
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}
	}
}

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
		camera->increaseScale();
		break;
	case(EventListener::Event::ZOOM_OUT):
		camera->decreaseScale();
		break;
	}
}





// Menu Setup

bool Game::initMenu(bool endGameScreen) {
	Size2D winSize(1920, 1080);

	//creates our renderer, which looks after drawing and the window
	renderer.init(winSize, "A Star Threading", camera);

	//// Load Image
	//if (endGameScreen == true)
	//{
	//	renderer.LoadImage("endScreen.jpg");
	//}
	//else
	//{
	//	renderer.LoadImage("menu.jpg");
	//}

	lastTime = LTimer::gameTime();

	//want game loop to pause
	inputManager.AddListener(EventListener::Event::QUIT, this);
	inputManager.AddListener(EventListener::Event::SPACE, this);
	inputManager.AddListener(EventListener::Event::ANYKEY, this);

	pause = false;
	quit = false;
	progress = false;
	return true;
}

void Game::updateMenu()
{
	unsigned int currentTime = LTimer::gameTime();//millis since game started
	unsigned int deltaTime = currentTime - lastTime;//time since last update

	////call update on all game objects
	//for (std::vector<Block*>::iterator i = blocks.begin(); i != blocks.end(); i++)
	//{
	//	(*i)->Update(deltaTime);
	//}

	//save the curent time for next frame
	lastTime = currentTime;
}

void Game::renderMenu()
{
	renderer.clear(Colour(147, 112, 219));// prepare for new frame

										  //render every object
	//for (std::vector<Block*>::iterator i = blocks.begin(), e = blocks.end(); i != e; i++)
	//{
	//	(*i)->Render(renderer);
	//}
	//renderer.RenderImage();

	renderer.present();// display the new frame (swap buffers)
}

void Game::loopMenu(bool endGameScreen)
{
	LTimer capTimer;//to cap framerate

	int frameNum = 0;
	while (!quit) { //game loop
		capTimer.start();

		inputManager.ProcessInput(endGameScreen);

		//if (!pause) //in pause mode don't bother updateing
			updateMenu();
		renderMenu();

		if (progress == true)
		{
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
