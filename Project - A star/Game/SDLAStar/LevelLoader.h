#pragma once
#define SDL_MAIN_HANDLED
#ifdef __APPLE__
#include "SDL2/SDL.h"
#elif defined(_WIN64) || defined(_WIN32)
#include "SDL.h"
#endif

#include "GameObject.h"
#include <vector>

class LevelLoader
{
public:
	LevelLoader();
	~LevelLoader();

	static LevelLoader* instance();

	std::vector<GameObject*> LoadLevel(int levelNumber);

private:
	static LevelLoader* _instance;
};

