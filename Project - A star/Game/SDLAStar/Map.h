#pragma once

#include <SDL.h>
#include <vector>

#include "Tile.h"

//#include "CSurface.h"

class Map
{
public:
	Map();
	~Map();

	SDL_Surface* Surf_Tileset;

	bool OnLoad();

	void OnRender(SDL_Surface* Surf_Display, int MapX, int MapY);

private:
	std::vector<Tile> TileList;

	int mapHeight;
	int mapWeight;
};

