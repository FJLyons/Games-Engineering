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
	if (listeners.find(evt) == listeners.end()) { //event not in map add it.
		listeners[evt] = new std::vector<EventListener*>();
	}

	listeners[evt]->push_back(listener);

}

//Send the events to interested objects
void InputManager::Dispatch(EventListener::Event evt)
{

	if (listeners.find(evt) != listeners.end()) {
		
		for (auto const &listener : *listeners[evt]) { //go through all listeners for this event
			listener->onEvent(evt); //Call on event for the listener

		}
	}
	
}


//Gnereate events
void InputManager::ProcessInput(bool endGameScreen)
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type) 
		{
			/* Keyboard event */
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
				}
				break;
			
			/* SDL_QUIT event (window close) */
			case SDL_QUIT:
				Dispatch(EventListener::Event::QUIT);
				break;

			default:
				break;
		}
	}
	//check for exit
}
