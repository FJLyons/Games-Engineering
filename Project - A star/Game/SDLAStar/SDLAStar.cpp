//  Defines the entry point for the console application.
//
#include "stdafx.h"

#include <iostream>
using namespace std;
#include "SceneManager.h"


/**Create and initialises an instance of game, and clean up when the game is closed*/

int main()
{
	SceneManager::instance()->startGame();

	return 0;
}

