#pragma once

#include <iostream>
using namespace std;
#include "Game.h"


class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	static SceneManager* instance();

	Game game[3];

	void init();

	void goToLevel(int levelNumber);

	void destroy();

	// Vriables
	int maxlevels;
	int currentLevel;

	bool gameOver;

private:
	static SceneManager* _instance;
};

