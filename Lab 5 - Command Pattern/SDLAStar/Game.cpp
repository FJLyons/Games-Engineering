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
	EventListener::Event testEvent = EventListener::Event::ESCAPE;
	Command* test = new SpaceCommand(std::bind(&Game::progressTest, this), EventListener::Type::Press);//////////////////////////////////////////

	Command* w = new SpaceCommand(std::bind(&Player::movePlayerUp, player), EventListener::Type::Hold);
	Command* a = new SpaceCommand(std::bind(&Player::movePlayerLeft, player), EventListener::Type::Hold);
	Command* s = new SpaceCommand(std::bind(&Player::movePlayerDown, player), EventListener::Type::Hold);
	Command* d = new SpaceCommand(std::bind(&Player::movePlayerRight, player), EventListener::Type::Hold);

	inputManager->AddKey(testEvent, test, this);
	inputManager->AddKey(EventListener::Event::BUTTON_DPAD_UP, w, this);
	inputManager->AddKey(EventListener::Event::BUTTON_DPAD_LEFT, a, this);
	inputManager->AddKey(EventListener::Event::BUTTON_DPAD_DOWN, s, this);
	inputManager->AddKey(EventListener::Event::BUTTON_DPAD_RIGHT, d, this);

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