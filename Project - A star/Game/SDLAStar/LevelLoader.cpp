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

std::vector<Tile*> LevelLoader::LoadLevel(int levelNumber)
{
	std::vector<Tile*> tiles;

	if (levelNumber == 1)
	{
		int size = 30;

		float divide = 30.3f;
		float width = 2000.0f / divide;
		float height = 2000.0f / divide;

		for (int x = 0; x < size; x++)
		{
			tileOne.push_back(std::vector<Tile*>());

			for (int y = 0; y < size; y++)
			{
				float xPos = x + (x * width);
				float yPos = y + (y * height);

				Tile* temp = new Tile(Rect(xPos, yPos, width, height), Tile::Type::FLOOR);


				// Create Spawn
				if (y >= 13 && y <= 26 && x >= 18 && x <= 27) { temp->setSpawn(); }

				// Create Goal
				if (y >= 9 && y <= 19 && x >= 2 && x <= 10) { temp->setGoal(); }

				// Create Walls
				if (x == 6 && y >= 3) { temp->setWall(); }
				if (x == 13 && y >= 1 && y <= 26) { temp->setWall(); }
				if (x == 20 && y >= 2 && y <= 27) { temp->setWall(); }

				tileOne[x].push_back(temp);

				tiles.push_back(temp);
			}
		}
	}

	else if (levelNumber == 2)
	{
		int size = 100;

		float divide = 100.0f;
		float width = 2000.0f / divide;
		float height = 2000.0f / divide;

		for (int x = 0; x < size; x++)
		{
			tileOne.push_back(std::vector<Tile*>());

			for (int y = 0; y < size; y++)
			{
				float xPos = 0 + (x * width);
				float yPos = 0 + (y * height);

				Tile* temp = new Tile(Rect(xPos, yPos, width, height), Tile::Type::FLOOR);

				if (y == 90)
				{
					temp->setWall();
				}

				tileOne[x].push_back(temp);

				tiles.push_back(temp);
			}
		}
	}

	else if (levelNumber == 3)
	{
		int size = 1000;

		float divide = 1000.0f;
		float width = 2000.0f / divide;
		float height = 2000.0f / divide;

		for (int x = 0; x < size; x++)
		{
			tileOne.push_back(std::vector<Tile*>());

			for (int y = 0; y < size; y++)
			{
				float xPos = 0 + (x * width);
				float yPos = 0 + (y * height);

				Tile* temp = new Tile(Rect(xPos, yPos, width, height), Tile::Type::FLOOR);

				if (y == 990)
				{
					temp->setWall();
				}

				tileOne[x].push_back(temp);

				tiles.push_back(temp);
			}
		}
	}

	return tiles;
}