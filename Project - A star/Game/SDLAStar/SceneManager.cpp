#include "stdafx.h"
#include "SceneManager.h"

SceneManager *SceneManager::_instance = 0;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	delete _instance;
}

SceneManager* SceneManager::instance()
{
	if (_instance == nullptr)
	{
		//if our instance hasn't been initialized initialize it
		_instance = new SceneManager();
	}
	//return the instance.
	return _instance;
}

void SceneManager::startMenu()
{
	endgamescreen = false;
	game[0].initMenu(endgamescreen);
	game[0].loopMenu(endgamescreen);
	game[0].destroy();
	currentLevel++;
	goToLevel(currentLevel);
}

void SceneManager::startGame()
{
	currentLevel = 0;
	maxlevels = 4;
	startMenu();
}

void SceneManager::goToLevel(int levelNumber)
{
	if (levelNumber != maxlevels)
	{
		if (!game[levelNumber].init(levelNumber)) {
			cout << "Failed to init game" << '\n';
		}
		game[levelNumber].loop();
		game[levelNumber].destroy();
		if (currentLevel != maxlevels)
		{
			currentLevel++;
			goToLevel(currentLevel);
		}
	}

	if (currentLevel == maxlevels)
	{
		endgamescreen = true;
		game[0].initMenu(endgamescreen);
		game[0].loopMenu(endgamescreen);
		game[0].destroy();
		currentLevel = 0;
		startMenu();
	}
}

void SceneManager::destroy()
{
	for (int i = 0; i < currentLevel; i++)
	{
		game[i].destroy();

	}
	exit(0);
}

