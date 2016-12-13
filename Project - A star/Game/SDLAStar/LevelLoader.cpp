#include "stdafx.h"
#include "LevelLoader.h"
#include "LTimer.h"
#include <iostream>


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
	{
		//if our instance hasn't been initialized initialize it
		_instance = new LevelLoader();
	}
	//return the instance.
	return _instance;
}

std::vector<std::vector<Tile*>> LevelLoader::LoadLevel(int levelNumber)
{
	// Clear previous level
	if (!tiles.empty())
	{
		for (int x = 0; x < tiles.size(); x++)
		{
			tiles[x].clear();
		}
 		tiles.clear();
		tiles.shrink_to_fit();
	}

	// Create Levels
	if (levelNumber == 0)
	{
		// Number of tiles up and across
		int size = 30; 

		// Tile Size
		float divide = 30.0f;
		float width = 2000.0f / divide;
		float height = 2000.0f / divide;

		// Walls
		const int borderWallAmount = 1; // Amount of walls touching border
		int borderWall = rand() % 10 + 9; // Area for border to spawn - center 3rd
		int borderLength = rand() % 15 + 4; // min length = 5 - max length = 20

		int innerWall[2]; // Amount of walls not touching sides
		int innerLength[2]; // length of walls
		for (int wallNumber = 0; wallNumber < 2; wallNumber++) // Loop through walls
		{
			innerWall[wallNumber] = rand() % 9 + (wallNumber * 20); // Area for inner walls - first and last 3rd
			innerLength[wallNumber] = rand() % 3 + 2; // min distance to wall = 3 - max distance to wall = 6
		}

		// Loop through Vector
		for (int x = 0; x < size; x++)
		{
			// Create vectors across
			tiles.push_back(std::vector<Tile*>());

			// Swap colours for checkerboard effect
			isEven = !isEven;

			for (int y = 0; y < size; y++)
			{
				// Set tile position
				float xPos = x * width;
				float yPos = y * height;
				
				// Tile
				Tile* temp = new Tile(Rect(xPos, yPos, width, height), Tile::Type::FLOORE, x, y);

				// Set floor type for checkerboard
				if (isEven == false)
				{
					temp->setFloorO(); // set floor to odd
					isEven = true;
				}
				else
				{
					isEven = false;
				}

				//// Create Spawn
				//if (y >= 13 && y <= 26 && x >= 18 && x <= 27) { temp->setSpawn(); }
				//// Create Goal
				//if (y >= 9 && y <= 19 && x >= 2 && x <= 10) { temp->setGoal(); }

				// Create walls
				if(x == borderWall && y >= borderLength){ temp->setWall(); }
				for (int wallNumber = 0; wallNumber < 2; wallNumber++)
				{
					if (x == innerWall[wallNumber] && 
						y >= innerLength[wallNumber] && 
						y < size - innerLength[wallNumber]) 
					{ temp->setWall(); }
				}

				// Add tile y to x vector
				tiles[x].push_back(temp);
			}
		}

		// return vector of vector of tiles
		return tiles;
	}

	else if (levelNumber == 1)
	{
		int size = 100;

		float divide = 100.0f;
		float width = 2000.0f / divide;
		float height = 2000.0f / divide;

		// Walls
		const int borderWallAmount = 2;
		int borderWall[borderWallAmount];
		int borderLength[borderWallAmount];
		for (int wallNumber = 0; wallNumber < borderWallAmount; wallNumber++)
		{
			borderWall[wallNumber] = rand() % 30 + 14  + (wallNumber * 30); // Area for border to spawn - second and fourth 5th
			borderLength[wallNumber] = rand() % 60 + 14; // min length = 15 - max length = 75
		}

		const int innerWallAmount = 4;
		int innerWall[innerWallAmount];
		int innerLength[innerWallAmount];
		for (int wallNumber = 0; wallNumber < innerWallAmount; wallNumber++)
		{
			innerWall[wallNumber] = rand() % 25 + (wallNumber * 25); // Area for inner walls - every quarter
			innerLength[wallNumber] = rand() % 10 + 9; // min distance to wall = 10 - max distance to wall = 20
		}

		// Stop walls placing on each other
		for (int wallNumberX = 0; wallNumberX < borderWallAmount; wallNumberX++)
		{
			for (int wallNumberY = 0; wallNumberY < innerWallAmount; wallNumberY++)
			{
				if (borderWall[wallNumberX] == innerWall[wallNumberY])
					innerWall[wallNumberY] += 5;
			}
		}

		for (int x = 0; x < size; x++)
		{
			tiles.push_back(std::vector<Tile*>());

			isEven = !isEven;

			for (int y = 0; y < size; y++)
			{
				float xPos = 0 + (x * width);
				float yPos = 0 + (y * height);

				Tile* temp = new Tile(Rect(xPos, yPos, width, height), Tile::Type::FLOORE, x, y);

				if (isEven == false)
				{
					temp->setFloorO();
					isEven = true;
				}
				else
				{
					isEven = false;
				}

				for (int wallNumber = 0; wallNumber < borderWallAmount; wallNumber++)
				{
						if (x == borderWall[0] && y >= borderLength[wallNumber]) { temp->setWall(); }
						if (x == borderWall[1] && y <= borderLength[wallNumber]) { temp->setWall(); }
				}

				for (int wallNumber = 0; wallNumber < innerWallAmount; wallNumber++)
				{
					if (x == innerWall[wallNumber] &&
						y >= innerLength[wallNumber] &&
						y < size - innerLength[wallNumber])
					{
						temp->setWall();
					}
				}
				
				tiles[x].push_back(temp);
			}
		}

		return tiles;
	}

	else if (levelNumber == 2)
	{
		int size = 1000;

		float divide = 1000.0f;
		float width = 2000.0f / divide;
		float height = 2000.0f / divide;

		// Walls
		const int borderWallAmount = 4;
		int borderWall[borderWallAmount];
		int borderLength[borderWallAmount];
		for (int wallNumber = 0; wallNumber < borderWallAmount; wallNumber++)
		{
			borderWall[wallNumber] = rand() % 200 + 50 + (wallNumber * 250); // Area for border to spawn - every 4th
			borderLength[wallNumber] = rand() % 750 + 100; // min length = 100 - max length = 850
		}

		const int innerWallAmount = 14;
		int innerWall[innerWallAmount];
		int innerLength[innerWallAmount];
		for (int wallNumber = 0; wallNumber < innerWallAmount; wallNumber++)
		{
			innerWall[wallNumber] = rand() % 65 + (wallNumber * 65); // Area for inner walls - every 14th
			innerLength[wallNumber] = rand() % 100 + 99; // min distance to wall = 100 - max distance to wall = 200
		}

		// Stop walls placing on each other
		for (int wallNumberX = 0; wallNumberX < borderWallAmount; wallNumberX++)
		{
			for (int wallNumberY = 0; wallNumberY < innerWallAmount; wallNumberY++)
			{
				if (borderWall[wallNumberX] == innerWall[wallNumberY])
					innerWall[wallNumberY] += 10;
			}
		}

		for (int x = 0; x < size; x++)
		{
			tiles.push_back(std::vector<Tile*>());

			isEven = !isEven;

			for (int y = 0; y < size; y++)
			{
				float xPos = 0 + (x * width);
				float yPos = 0 + (y * height);

				Tile* temp = new Tile(Rect(xPos, yPos, width, height), Tile::Type::FLOORE, x, y);

				if (isEven == false)
				{
					temp->setFloorO();
					isEven = true;
				}
				else
				{
					isEven = false;
				} 

				for (int wallNumber = 0; wallNumber < borderWallAmount; wallNumber++)
				{
					if (x == borderWall[0] && y >= borderLength[wallNumber]) { temp->setWall(); }
					if (x == borderWall[1] && y <= borderLength[wallNumber]) { temp->setWall(); }
					if (x == borderWall[2] && y >= borderLength[wallNumber]) { temp->setWall(); }
					if (x == borderWall[3] && y <= borderLength[wallNumber]) { temp->setWall(); }
				}

				for (int wallNumber = 0; wallNumber < innerWallAmount; wallNumber++)
				{
					if (x == innerWall[wallNumber] &&
						y >= innerLength[wallNumber] &&
						y < size - innerLength[wallNumber])
					{
						temp->setWall();
					}
				}

				tiles[x].push_back(temp);
			}
		}

		return tiles;
	}
}