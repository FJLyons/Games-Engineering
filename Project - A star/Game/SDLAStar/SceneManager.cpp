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

void SceneManager::init()
{
	currentLevel = 0;
	maxlevels = 2;
	goToLevel(0);
}

void SceneManager::goToLevel(int levelNumber)
{
	if (!game[levelNumber].init(levelNumber)) 
	{
		cout << "Failed to init game" << '\n';
	}
	game[levelNumber].loop();
	game[levelNumber].destroy();

	if (currentLevel == maxlevels)
	{
		currentLevel = 0;
		goToLevel(currentLevel);
	}
	else if (currentLevel != maxlevels)
	{
		currentLevel++;
		goToLevel(currentLevel);
	}
}

void SceneManager::destroy()
{
	for (int i = 0; i < currentLevel; i++)
	{
		game[i].destroy();

	}
	exit(0); // Close Application
}

