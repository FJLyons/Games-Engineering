#include "stdafx.h"
#include "InputManager.h"


InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::AddListener(EventListener::Event evt,EventListener *listener)
{
	if (listeners.find(evt) == listeners.end()) 
	{ 
		//event not in map add it.
		listeners[evt] = new std::vector<EventListener*>();
	}

	listeners[evt]->push_back(listener);
}

//Send the events to interested objects
void InputManager::Dispatch(EventListener::Event evt)
{

	if (listeners.find(evt) != listeners.end()) 
	{
		//go through all listeners for this event
		for (auto const &listener : *listeners[evt]) 
		{ 
			listener->onEvent(evt); //Call on event for the listener
		}
	}	
}

void InputManager::Update(SDL_Event event)
{
	sdlEvent = event;
}

bool InputManager::KeyPressed(SDL_Keycode key)
{
	if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.sym == key)
	{
		return true;
		previousKey = key;
	}
	return false;
}

bool InputManager::KeyPressed(std::vector<SDL_Keycode> keys)
{
	for (int i = 0; i < keys.size(); i++)
	{
		if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.sym == keys[i])
		{
			return true;
			previousKeys.push_back(keys[i]);
		}
	}
	return false;
}

bool InputManager::KeyReleased(SDL_Keycode key)
{
	if (sdlEvent.type == SDL_KEYUP && sdlEvent.key.keysym.sym == key)
	{
		return true;
		previousKey = SDLK_UNKNOWN;
	}
	return false;
}

bool InputManager::KeyReleased(std::vector<SDL_Keycode> keys)
{
	for (int i = 0; i < keys.size(); i++)
	{
		if (sdlEvent.type == SDL_KEYUP && sdlEvent.key.keysym.sym == keys[i])
		{
			return true;
			previousKeys.empty();
		}
	}
	return false;
}

bool InputManager::KeyHeld(SDL_Keycode key)
{
	if (previousKey == key)
	{
		if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.sym == key)
		{
			return true;
			previousKey = key;
		}
	}
	return false;
}

bool InputManager::KeyHeld(std::vector<SDL_Keycode> keys)
{
	if (previousKeys == keys)
	{
		for (int i = 0; i < keys.size(); i++)
		{
			if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.sym == keys[i])
			{
				return true;
				previousKeys.push_back(keys[i]);
			}
		}
	}
	return false;
}

//Gnereate events
void InputManager::ProcessInput(bool endGameScreen)
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type) 
		{
			case SDL_KEYDOWN:
				if (endGameScreen == true && e.key.keysym.sym == SDLK_q)
				{
					Dispatch(EventListener::Event::QUIT);
				}
				else
				{
					Dispatch(EventListener::Event::ANYKEY);
				}

				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					Dispatch(EventListener::Event::QUIT);
					break;

				case SDLK_SPACE:
					Dispatch(EventListener::Event::SPACE);
					break;

				case SDLK_w:
					Dispatch(EventListener::Event::DOWN); // Flipped because drawing from the bottom left
					break; 

				case SDLK_s:
					Dispatch(EventListener::Event::UP);
					break;

				case SDLK_a:
					Dispatch(EventListener::Event::LEFT);
					break;

				case SDLK_d:
					Dispatch(EventListener::Event::RIGHT);
					break;

				case SDLK_DOWN:
					Dispatch(EventListener::Event::ZOOM_OUT);
					break;

				case SDLK_UP:
					Dispatch(EventListener::Event::ZOOM_IN);
					break;
				}
				break;
			
			/* SDL_QUIT event (window close) */
			case SDL_QUIT:
				Dispatch(EventListener::Event::QUIT);
				break;

			//case SDL_MOUSEWHEEL:
			//	if (e.wheel.y)
			//	{

			default:
				break;
		} // e.type
	}
	//check for exit
}
