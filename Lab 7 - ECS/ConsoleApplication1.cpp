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

	while (true)
	{
		hs.Update();
	}
	system("PAUSE");
}

