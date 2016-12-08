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
	enum ListType
	{
		ZERO,
		OPEN,
		CLOSED,
	};

	tileList openList;
	tileList finalPath;
	vector<vector<int>> listMap;

	int heuristic(Tile* current, Tile* end)
	{
		return abs(abs(current->xPos - end->xPos) + abs(current->yPos - end->yPos));
	}

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

	struct CompareNodes
	{
		bool operator() (Tile* lhs, Tile* rhs)
		{
			return rhs->FunctionCost > lhs->FunctionCost;
		}
	};

	tileList Find(Tile* startTile, Tile* endTile, std::vector<std::vector<Tile*>>& tiles)
	{
		Tile* currentTile = nullptr;
		resetLists(tiles);
		openList.push_back(startTile);

		// If open list empty there is no solution
		while (!openList.empty())
		{
			// current tile = best valued tile
			sort(openList.begin(), openList.end(), CompareNodes());
			currentTile = *openList.begin();

			// Find best node in the open list

			// If target reached
			if (currentTile->xPos == endTile->xPos && currentTile->yPos == endTile->yPos)
			{
				break;
			}

			// Add best tile to closed list, delete it from the open list
			listMap[currentTile->xPos][currentTile->yPos] = ListType::CLOSED;
			openList.erase(std::find(openList.begin(), openList.end(), currentTile));

			// Get surrounding nodes
			for (int i = 0; i < 4; i++)
			{
				int x = 0;
				int y = 0;
				if (i == 0) { x = currentTile->xPos - 1; y = currentTile->yPos; } // left
				else if (i == 1) { x = currentTile->xPos + 1; y = currentTile->yPos; } // right
				else if (i == 2) { x = currentTile->xPos; y = currentTile->yPos - 1; } // up
				else if (i == 3) { x = currentTile->xPos; y = currentTile->yPos + 1; } // down

				// Check to see if x/y are in range of map and not a wall
				bool isInXRange = (x >= 0 && x < tiles.size());
				bool isInYRange = (y >= 0 && y < tiles[0].size());
				if (!isInXRange || !isInYRange || tiles[x][y]->getType() == Tile::Type::WALL)
				{
					continue;
				}

				// If tile is in closed list, skip it
				if (listMap[x][y] == ListType::CLOSED)
				{
					continue;
				}

				// Added Cost for surrounding tile
				int totalCost = 0;
				totalCost = currentTile->GraphCost + 1; // Straight to next tile, 1 away

				// Create new surrounding tile for testing
				Tile* surroundingTile = nullptr;
				for (int j = 0; j < openList.size(); j++)
				{
					// if there is already a tile in the open list, reset it to this tile
					if (openList[j]->xPos == x && openList[j]->yPos == y)
					{
						surroundingTile = openList[j];
					}
				}

				// If tile is new to the open list
				if (surroundingTile == nullptr)
				{
					surroundingTile = tiles[x][y];

					surroundingTile->GraphCost = totalCost; // Distance to start

					surroundingTile->HeuristicCost = heuristic(surroundingTile, endTile);// Distance to end

					surroundingTile->FunctionCost = surroundingTile->GraphCost + surroundingTile->HeuristicCost; // Total distance

					surroundingTile->parentTile = currentTile;


					listMap[surroundingTile->xPos][surroundingTile->yPos] = ListType::OPEN;
					openList.push_back(surroundingTile);
				}

				// Change G score and parent of surrounding tile
				else if (totalCost <= surroundingTile->GraphCost)
				{
					surroundingTile->GraphCost = totalCost; // Distance to start

					surroundingTile->HeuristicCost = heuristic(surroundingTile, endTile); // Distance to end
					
					surroundingTile->FunctionCost = surroundingTile->GraphCost + surroundingTile->HeuristicCost; // Total distance

					surroundingTile->parentTile = currentTile;
				}
			}
		}					// open list is empty

		// Produce path
		while (currentTile != nullptr)
		{
			currentTile->setPath();
			finalPath.push_back(currentTile);
			currentTile = currentTile->parentTile;
		}
		
		return finalPath;
	} // A Star

	void resetLists(std::vector<std::vector<Tile*>>& tiles)
	{
		listMap.erase(listMap.begin(), listMap.end());
		finalPath.erase(finalPath.begin(), finalPath.end());
		openList.erase(openList.begin(), openList.end());
		setupListMap(tiles);
	}



	void setupListMap(std::vector<std::vector<Tile*>>& tiles)
	{
		int tileMapSize = tiles.size();

		for (int i = 0; i < tileMapSize; i++)
		{
			listMap.push_back(vector<int>());

			for (int j = 0; j < tileMapSize; j++)
			{
				listMap[i].push_back(ListType::ZERO);
			}
		}
	}
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