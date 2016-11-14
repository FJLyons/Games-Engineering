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

	void startMenu();
	void startGame();

	void goToLevel(int levelNumber);

	void destroy();
	int maxlevels;
	int currentLevel;
	Game game[4];
	bool endgamescreen;

private:
	static SceneManager* _instance;
};

