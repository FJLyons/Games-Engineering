#include "stdafx.h"
#include "Map.h"


Map::Map()
{
	Surf_Tileset = NULL;
}


Map::~Map()
{
}

bool Map::OnLoad() {
	TileList.clear();

	for (int Y = 0; Y < mapHeight; Y++) {
		for (int X = 0; X < mapWeight; X++) {
			Tile tempTile;

			tempTile.TileID = 0;
			tempTile.TypeID = tempTile.TILE_TYPE_NORMAL;

			TileList.push_back(tempTile);
		}
	}

	return true;
}

void Map::OnRender(SDL_Surface* Surf_Display, int MapX, int MapY) {
	if (Surf_Tileset == NULL) return;

	int TilesetWidth = Surf_Tileset->w / ;
	int TilesetHeight = Surf_Tileset->h / TILE_SIZE;

	int ID = 0;

	for (int Y = 0; Y < mapHeight; Y++) {
		for (int X = 0; X < mapHeight; X++) {
			if (TileList[ID].TypeID == mapHeight) {
				ID++;
				continue;
			}

			int tX = MapX + (X * TILE_SIZE);
			int tY = MapY + (Y * TILE_SIZE);

			int TilesetX = (TileList[ID].TileID % TilesetWidth) * TILE_SIZE;
			int TilesetY = (TileList[ID].TileID / TilesetWidth) * TILE_SIZE;

			CSurface::OnDraw(Surf_Display, Surf_Tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);

			ID++;
		}
	}
}