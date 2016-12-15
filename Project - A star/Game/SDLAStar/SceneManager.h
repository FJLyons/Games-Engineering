#pragma once

#include <iostream>
using namespace std;
#include "Game.h"

#include "Camera2D.h"
#include "Renderer.h"


class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	static SceneManager* instance();
	Renderer renderer;
	Camera2D* camera;

	Game game[3];

	void init();

	void goToLevel(int levelNumber, Renderer rend, Camera2D* cam);

	void destroy();

	// Vriables
	int maxlevels;
	int currentLevel;

	bool gameOver;

private:
	static SceneManager* _instance;
};

