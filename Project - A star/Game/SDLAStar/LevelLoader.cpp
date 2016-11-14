#include "stdafx.h"
#include "LevelLoader.h"


LevelLoader *LevelLoader::_instance = 0;

LevelLoader::LevelLoader()
{
}

LevelLoader::~LevelLoader()
{
	delete _instance;
}

/**Singleton instance*/
LevelLoader* LevelLoader::instance()
{
	if (_instance == nullptr)
	{//if our instance hasn't been initialized
	 //initialize it
		_instance = new LevelLoader();
	}
	//return the instance.
	return _instance;
}

std::vector<GameObject*> LevelLoader::LoadLevel(int levelNumber)
{
	std::vector<GameObject*> tiles;

	if (levelNumber == 1 || levelNumber == 7)
	{

	}
	else if (levelNumber == 2)
	{

	}
	else if (levelNumber == 3)
	{

	}

	return tiles;
}