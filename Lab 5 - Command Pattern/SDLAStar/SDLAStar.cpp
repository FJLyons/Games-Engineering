//  Defines the entry point for the console application.
//
#include "stdafx.h"
#include <ctime>

#include <iostream>
using namespace std;
#include "Game.h"


/**Create and initialises an instance of game, and clean up when the game is closed*/

int main()
{
	srand(time(NULL));

	Game* game = new Game();
	Renderer renderer;

	Size2D winSize(1920, 1080);
	renderer.init(winSize, "Input Manager Application");

	if (!game->init(renderer))
	{
		cout << "Failed to init game" << '\n';
	}
	game->loop();
	game->destroy();

	return 0;
}

