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

class LevelLoader
{
public:
	LevelLoader();
	~LevelLoader();

	static LevelLoader* instance();

	std::vector<std::vector<Tile*>> LoadLevel(int levelNumber);

private:
	static LevelLoader* _instance;
	std::vector<std::vector<Tile*>> tileOne;
	std::vector<std::vector<Tile*>> tileTwo;
	std::vector<std::vector<Tile*>> tileTree;
};

