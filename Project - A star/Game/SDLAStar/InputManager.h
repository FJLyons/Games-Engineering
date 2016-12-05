#pragma once

#define SDL_MAIN_HANDLED
#ifdef __APPLE__
#include "SDL2/SDL.h"
#elif defined(_WIN64) || defined(_WIN32)
#include "SDL.h"
#endif


#include<map>
#include<vector>

#include "EventListener.h"

/*Convert input into logical events*/
class InputManager
{
	//dictionary holding a list of litener objs for each event type
	std::map<EventListener::Event, 
		std::vector<EventListener*>* //pointer to vec of eventlisteners
		> listeners;

public:
	InputManager();
	~InputManager();

	void AddListener(EventListener::Event, EventListener*);
	void Dispatch(EventListener::Event);

	void ProcessInput(bool endGameScreen);

	void Update(SDL_Event event);

	bool KeyPressed(SDL_Keycode key);
	bool KeyPressed(std::vector<SDL_Keycode> keys);

	bool KeyReleased(SDL_Keycode key);
	bool KeyReleased(std::vector<SDL_Keycode> keys);

	bool KeyHeld(SDL_Keycode key);
	bool KeyHeld(std::vector<SDL_Keycode> keys);

private:
	SDL_Event sdlEvent;

	SDL_Keycode previousKey;
	std::vector<SDL_Keycode> previousKeys;
};

