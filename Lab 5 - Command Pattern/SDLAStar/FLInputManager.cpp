#include "stdafx.h"
#include "FLInputManager.h"

InputManager* InputManager::inputManagerInstance = nullptr;

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

InputManager* InputManager::getInstance()
{
	if (inputManagerInstance == nullptr)
	{
		inputManagerInstance = new InputManager();
	}
	return inputManagerInstance;
}

void InputManager::AddListener(EventListener::Event evt, EventListener *listener)
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

void InputManager::ProcessInput()
{
	SDL_Event evn;
	while (SDL_PollEvent(&evn) != 0)
	{
		// * Any Key
		if (evn.type == SDL_KEYDOWN)
		{
			std::cout << evn.key.keysym.sym << std::endl;
		}

		switch (evn.type)
		{
			//* Key Down
		case SDL_KEYDOWN:
			switch (evn.key.keysym.sym)
			{
			case SDLK_UNKNOWN:
				Dispatch(EventListener::Event::UNKNOWN);
				break;
			case SDLK_RETURN:
				Dispatch(EventListener::Event::RETURN);
				break;
			case SDLK_ESCAPE:
				Dispatch(EventListener::Event::ESCAPE);
				break;
			case SDLK_BACKSPACE:
				Dispatch(EventListener::Event::BACKSPACE);
				break;
			case SDLK_TAB:
				Dispatch(EventListener::Event::TAB);
				break;
			case SDLK_SPACE:
				Dispatch(EventListener::Event::SPACE);
				break;
			case SDLK_EXCLAIM:
				Dispatch(EventListener::Event::EXCLAIM);
				break;
			case SDLK_QUOTEDBL:
				Dispatch(EventListener::Event::QUOTEDBL);
				break;
			case SDLK_HASH:
				Dispatch(EventListener::Event::HASH);
				break;
			case SDLK_PERCENT:
				Dispatch(EventListener::Event::PERCENT);
				break;
			case SDLK_DOLLAR:
				Dispatch(EventListener::Event::DOLLAR);
				break;
			case SDLK_AMPERSAND:
				Dispatch(EventListener::Event::AMPERSAND);
				break;
			case SDLK_QUOTE:
				Dispatch(EventListener::Event::QUOTE);
				break;
			case SDLK_LEFTPAREN:
				Dispatch(EventListener::Event::LEFTPAREN);
				break;
			case SDLK_RIGHTPAREN:
				Dispatch(EventListener::Event::RIGHTPAREN);
				break;
			case SDLK_ASTERISK:
				Dispatch(EventListener::Event::ASTERISK);
				break;
			case SDLK_PLUS:
				Dispatch(EventListener::Event::PLUS);
				break;
			case SDLK_COMMA:
				Dispatch(EventListener::Event::COMMA);
				break;
			case SDLK_MINUS:
				Dispatch(EventListener::Event::MINUS);
				break;
			case SDLK_PERIOD:
				Dispatch(EventListener::Event::PERIOD);
				break;
			case SDLK_SLASH:
				Dispatch(EventListener::Event::SLASH);
				break;
			case SDLK_0:
				Dispatch(EventListener::Event::NUM_0);
				break;
			case SDLK_1:
				Dispatch(EventListener::Event::NUM_1);
				break;
			case SDLK_2:
				Dispatch(EventListener::Event::NUM_2);
				break;
			case SDLK_3:
				Dispatch(EventListener::Event::NUM_3);
				break;
			case SDLK_4:
				Dispatch(EventListener::Event::NUM_4);
				break;
			case SDLK_5:
				Dispatch(EventListener::Event::NUM_5);
				break;
			case SDLK_6:
				Dispatch(EventListener::Event::NUM_6);
				break;
			case SDLK_7:
				Dispatch(EventListener::Event::NUM_7);
				break;
			case SDLK_8:
				Dispatch(EventListener::Event::NUM_8);
				break;
			case SDLK_9:
				Dispatch(EventListener::Event::NUM_9);
				break;
			case SDLK_COLON:
				Dispatch(EventListener::Event::COLON);
				break;
			case SDLK_SEMICOLON:
				Dispatch(EventListener::Event::SEMICOLON);
				break;
			case SDLK_LESS:
				Dispatch(EventListener::Event::LESS);
				break;
			case SDLK_EQUALS:
				Dispatch(EventListener::Event::EQUALS);
				break;
			case SDLK_GREATER:
				Dispatch(EventListener::Event::GREATER);
				break;
			case SDLK_QUESTION:
				Dispatch(EventListener::Event::QUESTION);
				break;
			case SDLK_AT:
				Dispatch(EventListener::Event::AT);
				break;
			case SDLK_LEFTBRACKET:
				Dispatch(EventListener::Event::LEFTBRACKET);
				break;
			case SDLK_BACKSLASH:
				Dispatch(EventListener::Event::BACKSLASH);
				break;
			case SDLK_RIGHTBRACKET:
				Dispatch(EventListener::Event::RIGHTBRACKET);
				break;
			case SDLK_CARET:
				Dispatch(EventListener::Event::CARET);
				break;
			case SDLK_UNDERSCORE:
				Dispatch(EventListener::Event::UNDERSCORE);
				break;
			case SDLK_BACKQUOTE:
				Dispatch(EventListener::Event::BACKQUOTE);
				break;
			case SDLK_a:
				Dispatch(EventListener::Event::a);
				break;
			case SDLK_b:
				Dispatch(EventListener::Event::b);
				break;
			case SDLK_c:
				Dispatch(EventListener::Event::c);
				break;
			case SDLK_d:
				Dispatch(EventListener::Event::d);
				break;
			case SDLK_e:
				Dispatch(EventListener::Event::e);
				break;
			case SDLK_f:
				Dispatch(EventListener::Event::f);
				break;
			case SDLK_g:
				Dispatch(EventListener::Event::g);
				break;
			case SDLK_h:
				Dispatch(EventListener::Event::h);
				break;
			case SDLK_i:
				Dispatch(EventListener::Event::i);
				break;
			case SDLK_j:
				Dispatch(EventListener::Event::j);
				break;
			case SDLK_k:
				Dispatch(EventListener::Event::k);
				break;
			case SDLK_l:
				Dispatch(EventListener::Event::l);
				break;
			case SDLK_m:
				Dispatch(EventListener::Event::m);
				break;
			case SDLK_n:
				Dispatch(EventListener::Event::n);
				break;
			case SDLK_o:
				Dispatch(EventListener::Event::o);
				break;
			case SDLK_p:
				Dispatch(EventListener::Event::p);
				break;
			case SDLK_q:
				Dispatch(EventListener::Event::q);
				break;
			case SDLK_r:
				Dispatch(EventListener::Event::r);
				break;
			case SDLK_s:
				Dispatch(EventListener::Event::s);
				break;
			case SDLK_t:
				Dispatch(EventListener::Event::t);
				break;
			case SDLK_u:
				Dispatch(EventListener::Event::u);
				break;
			case SDLK_v:
				Dispatch(EventListener::Event::v);
				break;
			case SDLK_w:
				Dispatch(EventListener::Event::w);
				break;
			case SDLK_x:
				Dispatch(EventListener::Event::x);
				break;
			case SDLK_y:
				Dispatch(EventListener::Event::y);
				break;
			case SDLK_z:
				Dispatch(EventListener::Event::z);
				break;
			}
			break;

			//* Quit Application
		case SDL_QUIT:
			Dispatch(EventListener::Event::ESCAPE);
			break;

			//* Else Break
		default:
			break;
		}
	}
}