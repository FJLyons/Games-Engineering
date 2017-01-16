#pragma once

#include <vector>

#include "Renderer.h"
#include "GameObject.h"
//#include "EventListener.h"
//#include "InputManager.h"

#include "Player.h"

#include "FLInputManager.h"


/** The game object which manages the game loop*/
class Game : public EventListener
{
	InputManager* inputManager = InputManager::getInstance();
	Renderer renderer;

	Player* player;

	float scale;
	int levelSize;

	// Variables
	unsigned int lastTime; // time of last update;

	bool progress; // Move to next level
	bool quit; // quit app

	bool threaded = true;


public:
	Game();
	~Game();

	bool init(Renderer rend);
	void update();
	void render();
	void loop();

	void destroy();
	void onEvent(EventListener::Event);

	void progressTest();

	int test = 0;
};

class SpaceCommand : public Command
{
public:
	SpaceCommand(std::function<void()> function) : Command(function) {}
	virtual void execute()
	{
		m_function();
	}
};

