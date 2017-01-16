#include "stdafx.h"

#include <iostream>
using namespace std;
#include <chrono>
#include <thread>

#include "LTimer.h"
#include "Game.h"

const int SCREEN_FPS = 1000000;
const int SCREEN_TICKS_PER_FRAME = 1 / SCREEN_FPS;

Game::Game()
{
	quit = false;
}

Game::~Game()
{
}

bool Game::init(Renderer rend) {	
	// Set Window Size
	Size2D winSize(2000, 2000);
	renderer = rend;

	// Time
	lastTime = LTimer::gameTime();

	// Player
	player = new Player();
	
	// Events
	inputManager->AddListener(EventListener::Event::SPACE, this);//////////////////////////////////////////////////////////////
	inputManager->Key_SPACE = new SpaceCommand(std::bind(&Game::progressTest, this));//////////////////////////////////////////


	inputManager->AddListener(EventListener::Event::w, this);
	inputManager->Key_w = new SpaceCommand(std::bind(&Player::movePlayerUp, player));
	inputManager->AddListener(EventListener::Event::a, this);
	inputManager->Key_a = new SpaceCommand(std::bind(&Player::movePlayerLeft, player));
	inputManager->AddListener(EventListener::Event::s, this);
	inputManager->Key_s = new SpaceCommand(std::bind(&Player::movePlayerDown, player));
	inputManager->AddListener(EventListener::Event::d, this);
	inputManager->Key_d = new SpaceCommand(std::bind(&Player::movePlayerRight, player));

	// Bools
	quit = false;
	progress = false;


	return true;
}

void Game::update()
{
	unsigned int currentTime = LTimer::gameTime();//millis since game started
	float deltaTime = (currentTime - lastTime) / 1000.0;//time since last update

	//save the curent time for next frame
	lastTime = currentTime;

	player->Update(deltaTime);
}

void Game::render()
{
	renderer.clear(Colour(0,0,0));// prepare for new frame

	player->Render(renderer);

	renderer.present();// display the new frame (swap buffers)
}

void Game::loop()
{
	LTimer capTimer; // cap framerate

	while (!quit) 
	{ 
		//game loop
		capTimer.start();

		inputManager->ProcessInput();////////////////////////////////////////////////////////////////////////////////////////////

		update();
		render();

		int frameTicks = capTimer.getTicks();//time since start of frame
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			//Wait remaining time before going to next frame
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}

		if (progress == true)
		{
			break;
		}
	}
}

// Event manager
void Game::onEvent(EventListener::Event evt)
{
	switch (evt)
	{
	case (EventListener::Event::SPACE):////////////////////////////////////////////////////////////////////////////////////////
		inputManager->Key_SPACE->execute();////////////////////////////////////////////////////////////////////////////////////
		break;
	case (EventListener::Event::w):
		inputManager->Key_w->execute();
		break;
	case (EventListener::Event::a):
		inputManager->Key_a->execute();
		break;
	case (EventListener::Event::s):
		inputManager->Key_s->execute();
		break;
	case (EventListener::Event::d):
		inputManager->Key_d->execute();
		break;
	}
}

// Close app
void Game::destroy()
{
	renderer.destroy();
	exit(0);
}

void Game::progressTest()
{
	progress = true;
}