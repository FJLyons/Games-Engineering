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

	//creates our renderer, which looks after drawing and the window
	renderer.init(winSize, "A Star Threading");

	//set up the viewport
	Size2D vpSize(2000, 2000);
	Point2D vpBottomLeft(0, 0);

	Rect vpRect(vpBottomLeft, vpSize);
	renderer.setViewPort(vpRect);

	// Objects
	tiles = LevelLoader::instance()->LoadLevel(levelNumber);

	//if (levelNumber == 1)
	//{
	//	startTile = tiles[0][0];
	//	endTile = tiles[19][19];
	//}
	//else if (levelNumber == 2)
	//{
	//	startTile = tiles[0][0];
	//	endTile = tiles[99][99];
	//}
	//else if (levelNumber == 3)
	//{
	//	startTile = tiles[0][0];
	//	endTile = tiles[999][999];
	//}

	startTile = tiles[0][0];
	endTile = tiles[19][19];
	pathfinder->Find(startTile, endTile,  tiles);

	// Time
	lastTime = LTimer::gameTime();
	
	// Events
	inputManager.AddListener(EventListener::Event::QUIT, this);
	inputManager.AddListener(EventListener::Event::SPACE, this);
	inputManager.AddListener(EventListener::Event::ANYKEY, this);

	// Bools
	progress = false;

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
	
	//render every object
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles.size(); j++)
		{
			tiles.at(i).at(j)->Render(renderer);
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

void Game::onEvent(EventListener::Event evt) {
		
	if (evt == EventListener::Event::QUIT) {
		SceneManager::instance()->destroy();
	}

	if (evt == EventListener::Event::SPACE) {
		progress = true;
	}

	if (evt == EventListener::Event::ANYKEY) {
		
	}
}





// Menu Setup

bool Game::initMenu(bool endGameScreen) {
	Size2D winSize(1920, 1080);

	//creates our renderer, which looks after drawing and the window
	renderer.init(winSize, "A Star Threading");

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
