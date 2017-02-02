#include <stdafx.h>
#include <string>
#include <iostream>
#include <thread>

#include "Classes.h"

int main() 
{
	Entity player;

	HealthComponenet* hc = new HealthComponenet();
	player.AddComponent(Health, hc);

	HealthSystem hs;
	hs.AddEntity(player);

	PositionComponenet* pc = new PositionComponenet();
	player.AddComponent(Position, pc);
	PositionComponenet* pc2 = new PositionComponenet();
	player.AddComponent(Position, pc2);

	PositionSystem ps;
	ps.AddEntity(player);

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		hs.Update();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		ps.Update();
	}
	system("PAUSE");
}

