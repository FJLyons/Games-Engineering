#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue> 

#include "Tile.h"


using namespace std;

class Pathfinder
{
public:

	typedef vector<Tile*> tileList;

	tileList Find(Tile* startTile, Tile* endTile, std::vector<std::vector<Tile*>>& tiles)
	{
		tileList finalPath, closedList, openList;

		openList.push_back(startTile);

		// If open list empty there is no solution
		while (!openList.empty())
		{
			int bestIndex = 0;
			int bestF = 100000;

			// Find best node in the open list
			for (int i = 0; i < openList.size(); i++)
			{
				if (openList[i]->F < bestF)
				{
					bestF = openList[i]->F;
					bestIndex = i;
				}
			}

			Tile* b = openList[bestIndex];
			b->setSpawn();
			closedList.push_back(b);
			openList.erase(openList.begin() + bestIndex);

			if (b->xPos == endTile->xPos && b->yPos == endTile->yPos)
			{
				Tile* currentTileInPath = endTile;

				while (currentTileInPath != startTile)
				{
					finalPath.push_back(currentTileInPath);
					currentTileInPath = currentTileInPath->parentTile;
					currentTileInPath->setPath();
				}

				return finalPath; // if current pos == end pos
			}

			// Get surrounding nodes
			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					int x1 = b->xPos + x;
					int y1 = b->yPos + y;

					bool isInXRange = (x1 >= 0 && x1 < tiles.size());
					bool isInYRange = (y1 >= 0 && y1 < tiles[0].size());

					Tile* xT = (isInXRange && isInYRange) ? tiles[x1][y1] : NULL;

					if (xT != NULL)
					{
						// If walkable tile...
						if (xT->getType() != Tile::Type::WALL)
						{
							// If not in open or closed list
							if (!(std::find(openList.begin(), openList.end(), xT) != openList.end()) &&
								!(std::find(closedList.begin(), closedList.end(), xT) != closedList.end()))
							{
								xT->parentTile = b;

								// calculate G, H, F values								
								int numStraightG = abs(xT->xPos - b->xPos) + abs(xT->yPos - b->yPos);
								if (numStraightG == 1)
									xT->G = b->G + 10;
								else
									xT->G = b->G + 20;

								//xT->G = abs(xT->xPos - startTile->xPos) + abs(xT->yPos - startTile->yPos);


								int xMove = abs(xT->xPos - endTile->xPos);
								int yMove = abs(xT->yPos - endTile->yPos);
								int xDiff = xMove - yMove;
								int numStraights = abs(xDiff);
								int numDiagonals = xMove <= yMove ? xMove : yMove;
								xT->H = (numStraights * 10) + (numDiagonals * 20);		// distance to end

								//xT->H = abs(xT->xPos - endTile->xPos) + abs(xT->yPos - endTile->yPos);

								xT->F = xT->G + xT->H; // total distance
								
								// add to open list
								openList.push_back(xT);
							}
						}
					}	// null check
				}		// y complete
			}			// x complete
		}				// open list is empty
	}					// done
};

//xT->G = abs(xT->xPos - startTile->xPos) + abs(xT->yPos - startTile->yPos);	// distance to start
//xT->H = abs(xT->xPos - endTile->xPos) + abs(xT->yPos - endTile->yPos);		// distance to end
