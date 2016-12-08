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

	bool isInList(tileList list, int x, int y)
	{
		for (int i = 0; i < list.size(); i++)
		{
			//list[i]->setSpawn();
			if (list[i]->xPos == x && list[i]->yPos == y)
			{
				return true;
			}
		}
		return false;
	}


	tileList Find(Tile* startTile, Tile* endTile, std::vector<std::vector<Tile*>>& tiles)
	{
		Tile* currentTile = nullptr;

		tileList closedList, openList;

		openList.push_back(startTile);

		// If open list empty there is no solution
		while (!openList.empty())
		{
			// current tile = best valued tile
			currentTile = *openList.begin();

			// Find best node in the open list
			for (int i = 0; i < openList.size(); i++)
			{
				if (openList[i]->F <= currentTile->F)
				{
					currentTile = openList[i];
					std::cout << "X:\t" << currentTile->xPos 
					<< "\t" << "Y:\t" << currentTile->yPos << std::endl;
				}
			}

			// If target reached
			if (currentTile->xPos == endTile->xPos && currentTile->yPos == endTile->yPos)
			{
				break;
			}

			// Add best tile to closed list, delete it from the open list
			closedList.push_back(currentTile);
			openList.erase(std::find(openList.begin(), openList.end(), currentTile));

			// Get surrounding nodes
			for (int x = currentTile->xPos - 1; x <= currentTile->xPos + 1; x++)
			{
				for (int y = currentTile->yPos - 1; y <= currentTile->yPos + 1; y++)
				{
					// If tile is in closed list, skip it
					if (isInList(closedList, x, y))
					{
						continue;
					}

					// Check to see if x/y are in range of map
					bool isInXRange = (x >= 0 && x < tiles.size());
					bool isInYRange = (y >= 0 && y < tiles[0].size());
					if (!isInXRange || !isInYRange || tiles[x][y]->getType() == Tile::Type::WALL)
					{
						continue;
					}

					// Added Cost for surrounding tile
					int totalCost = 0;
					if (x == 0 || y == 0) { totalCost = currentTile->G + 1.0f; } // Straight
					else { totalCost = currentTile->G + 1.4f; } // diagonal
					
					// Create new surrounding tile for testing
					Tile* surroundingTile = nullptr;
					for (int i = 0; i < openList.size(); i++)
					{
						// if there is already a tile in the open list, reset it to this tile
						if (openList[i]->xPos == x && openList[i]->yPos == y)
						{
							surroundingTile = openList[i];
						}
					}

					// If tile is new to the open list
					if (surroundingTile == nullptr)
					{
						surroundingTile = tiles[x][y];
						surroundingTile->G = totalCost; // distance to start

						int diff = abs(surroundingTile->xPos - endTile->xPos) + abs(surroundingTile->yPos - endTile->yPos);
						surroundingTile->H = diff; // distance to end

						surroundingTile->F = surroundingTile->G + surroundingTile->H; // total distance

						surroundingTile->parentTile = currentTile;

						openList.push_back(surroundingTile);
					}

					// Change G score and parent of surrounding tile
					else if (totalCost < surroundingTile->G)
					{
						surroundingTile->parentTile = currentTile;

						surroundingTile->G = totalCost;

						int diff = abs(surroundingTile->xPos - endTile->xPos) + abs(surroundingTile->yPos - endTile->yPos); // distance to start
						surroundingTile->H = diff; // distance to end

						surroundingTile->F = surroundingTile->G + surroundingTile->H; // total distance
					}					
				}			// y complete
			}				// x complete
		}					// open list is empty

		// Produce path
		tileList finalPath;
		while (currentTile != nullptr)
		{
			currentTile->setPath();
			finalPath.push_back(currentTile);
			currentTile = currentTile->parentTile;
		}

		openList.clear();
		closedList.clear();

		return finalPath;
	}	// done
};

//surroundingTile->G = abs(surroundingTile->xPos - startTile->xPos) + abs(surroundingTile->yPos - startTile->yPos);	// distance to start
//surroundingTile->H = abs(surroundingTile->xPos - endTile->xPos) + abs(surroundingTile->yPos - endTile->yPos);		// distance to end

//int numStraightG = abs(surroundingTile->xPos - bestTile->xPos) - abs(surroundingTile->yPos - bestTile->yPos);

//int numStraightH = abs(diff);
//int numDiagonalH = xMove <= yMove ? xMove : yMove;
//surroundingTile->H = (numStraightH * 10) + (numDiagonalH * 14);		// distance to end

//// Swap path if distance is smaller
//for (int i = 0; i < openList.size(); i++)
//{
//	if (surroundingTile->F <= openList[i]->F)
//	{
//		Tile* temp = surroundingTile;
//		surroundingTile = openList[i];
//		openList[i] = temp;
//	}
//}


// Create surrounding tile and check its in range, else null
//Tile* surroundingTile = (isInXRange && isInYRange) ? tiles[x][y] : NULL;

//if (surroundingTile != NULL)
//{
//	//// If walkable tile...
//	if (surroundingTile->getType() != Tile::Type::WALL)
//	{
//	// If not in open or closed list
//		if (!(std::find(openList.begin(), openList.end(), surroundingTile) != openList.end()) &&
//			!(std::find(closedList.begin(), closedList.end(), surroundingTile) != closedList.end()))
//		{
//			surroundingTile->parentTile = currentTile;
//
//			// calculate cost of edge and cost of previous node								
//			if (abs(surroundingTile->xPos - currentTile->xPos) == 1 && abs(surroundingTile->yPos - currentTile->yPos) == 1)
//			{
//				surroundingTile->G = currentTile->G + 14; // distance to start
//			}
//			else
//			{
//				surroundingTile->G = currentTile->G + 10; // distance to start
//			}
//
//			// estimated cost to target
//
//			//edge + previous cost + estimate = a*
//			surroundingTile->F = surroundingTile->G + surroundingTile->H + currentTile->F; // total distance
//
//																						   // add to open list
//			openList.push_back(surroundingTile);
//		}
//	}	// Wall check
//}		// null check


//int bestIndex = 0;
//int bestF = 100000;


//Tile* bestTile = openList[bestIndex];
//bestTile->setSpawn();
//closedList.push_back(bestTile);
//openList.erase(openList.begin() + bestIndex);


//Tile* currentTileInPath = endTile;

//while (currentTileInPath != startTile)
//{
//	finalPath.push_back(currentTileInPath);
//	currentTileInPath = currentTileInPath->parentTile;
//	currentTileInPath->setPath();
//}

//return finalPath; // if current pos == end pos