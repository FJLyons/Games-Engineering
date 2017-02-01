#include <stdafx.h>
#include <string>
#include <iostream>
#include <thread>

#include "Classes.h"

// Needed for circular dependancy
void Falling::Update(GameObject& object)
{
	std::cout << "Falling\n";
	object.SetState(new Waiting());
}

int main() 
{
	GameObject state(new Waiting());
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
		state.Update();
	}
	system("PAUSE");
}

