#pragma once
#define SDL_MAIN_HANDLED
#ifdef __APPLE__
#include "SDL2/SDL.h"
#elif defined(_WIN64) || defined(_WIN32)
#include "SDL.h"
#endif

#include "GameObject.h"
#include <vector>

#include "Tile.h"
#include "Pathfinder.h"

class LevelLoader
{
public:
	LevelLoader();
	~LevelLoader();

	static LevelLoader* instance();

	std::vector<std::vector<Tile*>> LoadLevel(int levelNumber);

	bool isEven = false;

	void addWaypoints();

private:
	static LevelLoader* _instance;
	std::vector<std::vector<Tile*>> tiles;
	std::vector<std::vector<Tile*>> waypoints;

	int borderWallX[4];
	int borderWallY[4];
	int innerWallX[14];
	int innerWallY[14];

	int borderWalls[4];
	int innerWalls[14];
};

