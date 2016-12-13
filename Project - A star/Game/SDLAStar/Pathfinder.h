#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue> 

#include "Tile.h"

//class Enemy;

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

	struct TileInfo
	{
		int GraphCost = 10000000;
		int HeuristicCost = 0;
		int FunctionCost = 0;
		int listType = ListType::ZERO;
		Tile* parentTile = nullptr;
	};

	void initializeTileData(vector<vector<TileInfo>>* tileData, std::vector<std::vector<Tile*>>* tiles)
	{
		int tileMapSize = tiles->size();

		for (int i = 0; i < tileMapSize; i++)
		{
			tileData->push_back(vector<TileInfo>());

			for (int j = 0; j < tileMapSize; j++)
			{
				tileData->at(i).push_back(TileInfo());
			}
		}
	}

	int heuristic(Tile* current, Tile* end)
	{
		return abs(abs(current->xPos - end->xPos) + abs(current->yPos - end->yPos));
	}

	tileList Find(Tile* startTile, Tile* endTile, std::vector<std::vector<Tile*>>& tiles)
	{
		tileList openList;
		tileList finalPath;

		vector<vector<TileInfo>> tileData; // map of Tile information
		initializeTileData(&tileData, &tiles);

		Point2D startTilePos = startTile->getIndexPosition();
		TileInfo* startTileInfo = &tileData.at(startTilePos.x).at(startTilePos.y);

		startTileInfo->GraphCost = 0;
		startTileInfo->HeuristicCost = heuristic(startTile, endTile);
		startTileInfo->FunctionCost = startTileInfo->GraphCost + startTileInfo->HeuristicCost;

		openList.push_back(startTile);

		// If open list empty there is no solution
		while (!openList.empty())
		{
			// current tile = best valued tile
			Tile* currentTile = openList.back();

			// Tile traversal values
			Point2D currentTilePos = Point2D(currentTile->xPos, currentTile->yPos);
			TileInfo* currentTileInfo = &tileData[currentTilePos.x][currentTilePos.y];
			currentTileInfo->listType = ListType::CLOSED;
			openList.pop_back();
			
			// If target reached
			if (currentTile == endTile)
			{
				// Produce path
				while (currentTileInfo->parentTile != nullptr)
				{
					finalPath.push_back(currentTile);
//					enemy->currentPath.push_back(currentTile);

					currentTile->setPath();
					currentTile = currentTileInfo->parentTile;
					currentTilePos = currentTile->getIndexPosition();
					currentTileInfo = &tileData[currentTilePos.x][currentTilePos.y];
				}
				break;
			}
			
			// Get surrounding nodes
			for (int i = 0; i < 4; i++)
			{
				int x = 0;
				int y = 0;

				// Get neighbours
				if (i == 0) { x = currentTile->xPos + 1; y = currentTile->yPos; } // right
				else if (i == 1) { x = currentTile->xPos; y = currentTile->yPos + 1; } // down
				else if (i == 2) { x = currentTile->xPos - 1; y = currentTile->yPos; } // left
				else if (i == 3) { x = currentTile->xPos; y = currentTile->yPos - 1; } // up
				

				// Check to see if x/y are in range of map, and not a wall,
				bool isInXRange = (x >= 0 && x < tiles.size());
				bool isInYRange = (y >= 0 && y < tiles[0].size());
				if (!isInXRange || !isInYRange 
					|| tiles[x][y]->getType() == Tile::Type::WALL)
				{
					continue; // Exit current loop
				}

				// Added Cost for surrounding tile
				int totalGCost = currentTileInfo->GraphCost + 1; // Straight to next tile, 1 away

				// Create new surrounding tile for testing
				Tile* surroundingTile = tiles[x][y];
				Point2D surroundingTilePos = surroundingTile->getIndexPosition();
				TileInfo* surroundingTileInfo = &tileData[surroundingTilePos.x][surroundingTilePos.y];

				if(surroundingTileInfo->listType == ListType::CLOSED)
				{
					continue; // Exit current loop
				}

				// Change G score and parent of surrounding tile
				if (totalGCost < surroundingTileInfo->GraphCost)
				{
					surroundingTileInfo->GraphCost = totalGCost; // Distance to start
					surroundingTileInfo->HeuristicCost = heuristic(surroundingTile, endTile); // Distance to end					
					surroundingTileInfo->FunctionCost = surroundingTileInfo->GraphCost + surroundingTileInfo->HeuristicCost; // Total distance

					surroundingTileInfo->parentTile = currentTile;
				}

				// If tile is new to the open list
				if (surroundingTileInfo->listType != ListType::OPEN)
				{
					// Sorted insertion
					// Sorted insertion
					int sortIndex = openList.size() - 1;
					for (sortIndex; sortIndex >= 0; sortIndex--)
					{
						Point2D sortPos = openList[sortIndex]->getIndexPosition();
						TileInfo* sortInfo = &tileData[sortPos.x][sortPos.y];

						if (sortInfo->FunctionCost >= surroundingTileInfo->FunctionCost)
						{
							break;
						}
					}

					if (sortIndex < 0) { sortIndex = 0; }

					openList.insert(openList.begin() + sortIndex, surroundingTile);
					surroundingTileInfo->listType = ListType::OPEN;
					//surroundingTile->setEnemy();
				}
			}
		} // open list is empty
		
		return finalPath;
	} // A Star
};


//struct CompareNodes
//{
//	bool operator() (Tile* lhs, Tile* rhs)
//	{
//		return lhs->FunctionCost < rhs->FunctionCost;
//	}
//};


//// Add best tile to closed list, delete it from the open list
//listMap[currentTile->xPos][currentTile->yPos] = ListType::CLOSED;
//openList.erase(std::find(openList.begin(), openList.end(), currentTile));


//sort(openList.begin(), openList.end(), CompareNodes());




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