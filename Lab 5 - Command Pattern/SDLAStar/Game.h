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
	SpaceCommand(std::function<void()> function, EventListener::Type type) : Command(function, type) {}
	
	virtual void executePress()
	{
		for (int i = 0; m_type == EventListener::Type::Press && i < m_functions.size(); i++)
			m_functions[i]();
	}

	virtual void executeRelease()
	{
		for (int i = 0; m_type == EventListener::Type::Release && i < m_functions.size(); i++)
			m_functions[i]();
	}

	virtual void executeHold()
	{
		for (int i = 0; m_type == EventListener::Type::Hold && i < m_functions.size(); i++)
			m_functions[i]();
	}
};

