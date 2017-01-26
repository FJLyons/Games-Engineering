#include "stdafx.h"
#include "FLInputManager.h"

//* Set initial instance to be nullptr
InputManager* InputManager::inputManagerInstance = nullptr;

//* Default Constructor
InputManager::InputManager()
{
}

//* Default Deconstructor
InputManager::~InputManager()
{
}

//* Used to get the Class Instance
InputManager* InputManager::getInstance()
{
	if (inputManagerInstance == nullptr)
	{
		inputManagerInstance = new InputManager();
	}
	//* Used to return the same instance of the Class
	return inputManagerInstance;
}

//* Create an EventListener object
void InputManager::AddListener(EventListener::Event evt, EventListener *listener)
{
	if (listeners.find(evt) == listeners.end())
	{
		listeners[evt] = new std::vector<EventListener*>();
	}

	listeners[evt]->push_back(listener);
}

//* Find a specific Event listener in the listeners dictionary, and call its onEvent() function
void InputManager::Dispatch(EventListener::Type type, EventListener::Event evt)
{
	if (listeners.find(evt) != listeners.end())
	{
		for (auto const &listener : *listeners[evt])
		{
			listener->onEvent(evt);
		}
	}

	//*After a key is dispatched, see if it was previously held
	CheckPrevious(type, evt);
}

//* Set the hold for a specific Event in the beingHeld dictionary 
void InputManager::SetPrevious(EventListener::Event evt, bool isHeld)
{
	//* Set Event in map hold to be true or false
	beingHeld[evt] = isHeld;
}

//* Check to see if a specific Event is being held down
void InputManager::CheckPrevious(EventListener::Type type, EventListener::Event evt)
{
	//* Set Held to false for Event if the key was released
	if (type == EventListener::Type::Release)
	{
		SetPrevious(evt, false);
	}
	
	//* If Events hold is true, set Event Type to Hold
	if (beingHeld[evt])
	{
		type = EventListener::Type::Hold;
	}

	//// 0 if false, 1 if true - Uncomment if debugging hold functionality
	//std::cout << beingHeld[evt] << std::endl;

	//* Run the Events Execute, now that type has been determined
	Execute(type, evt);
}

//* Create a Command object
void InputManager::AddCommand(EventListener::Event evt, Command *command)
{
	if (commands.find(evt) == commands.end())
	{
		commands[evt] = new std::vector<Command*>();
	}

	commands[evt]->push_back(command);
}

//* Find a Command object in the commands dictionary, and call its execute function based on Event Type
void InputManager::Execute(EventListener::Type type, EventListener::Event evt)
{
	if (commands.find(evt) != commands.end())
	{
		for (auto const &command : *commands[evt])
		{
			//// Execution calls for firing custom function sent in
			if (type == EventListener::Type::Press) { command->executePress(); }
			else if (type == EventListener::Type::Release) { command->executeRelease(); }
			else if (type == EventListener::Type::Hold) { command->executeHold(); }
			else { command->execute(); }
		}
	}

	//* Set Held to true for Event if the key was released, based on type
	if (type == EventListener::Type::Press)
	{
		SetPrevious(evt, true);
	}
}

//* Used to create a key event
void InputManager::AddKey(EventListener::Event evt, Command* command, EventListener *listener)
{
	//* This shit is LIT yo!
	//* Get a Command* and set Reference to that Command* 
	Command*& toBind = bindCommand(evt);
	//* get the referenced Command*, and assign the desired Command*
	toBind = command;

	//* Create a Listener for this Event
	AddListener(evt, listener);
	//* Create a Command for this Event
	AddCommand(evt, toBind);
}

//* Combine a Command* and an EventListener to work together
Command*& InputManager::bindCommand(EventListener::Event evt)
{
	//* Return a Command* based on the Event
	switch (evt)
	{
	case SDLK_UNKNOWN:		return  Key_UNKNOWN;		break;
	case SDLK_RETURN:		return	Key_RETURN;			break;
	case SDLK_ESCAPE:		return	Key_ESCAPE;			break;
	case SDLK_BACKSPACE:	return	Key_BACKSPACE;		break;
	case SDLK_TAB:			return	Key_TAB;			break;
	case SDLK_SPACE:		return	Key_SPACE;			break;
	case SDLK_EXCLAIM:		return	Key_EXCLAIM;		break;
	case SDLK_QUOTEDBL:		return	Key_QUOTEDBL;		break;
	case SDLK_HASH:			return	Key_HASH;			break;
	case SDLK_PERCENT:		return	Key_PERCENT;		break;
	case SDLK_DOLLAR:		return	Key_DOLLAR;			break;
	case SDLK_AMPERSAND:	return	Key_AMPERSAND;		break;
	case SDLK_QUOTE:		return	Key_QUOTE;			break;
	case SDLK_LEFTPAREN:	return	Key_LEFTPAREN;		break;
	case SDLK_RIGHTPAREN:	return	Key_RIGHTPAREN;		break;
	case SDLK_ASTERISK:		return	Key_ASTERISK;		break;
	case SDLK_PLUS:			return	Key_PLUS;			break;
	case SDLK_COMMA:		return	Key_COMMA;			break;
	case SDLK_MINUS:		return	Key_MINUS;			break;
	case SDLK_PERIOD:		return	Key_PERIOD;			break;
	case SDLK_SLASH:		return	Key_SLASH;			break;
	case SDLK_0:			return	Key_NUM_0;			break;
	case SDLK_1:			return	Key_NUM_1;			break;
	case SDLK_2:			return	Key_NUM_2;			break;
	case SDLK_3:			return	Key_NUM_3;			break;
	case SDLK_4:			return	Key_NUM_4;			break;
	case SDLK_5:			return	Key_NUM_5;			break;
	case SDLK_6:			return	Key_NUM_6;			break;
	case SDLK_7:			return	Key_NUM_7;			break;
	case SDLK_8:			return	Key_NUM_8;			break;
	case SDLK_9:			return	Key_NUM_9;			break;
	case SDLK_COLON:		return	Key_COLON;			break;
	case SDLK_SEMICOLON:	return	Key_SEMICOLON;		break;
	case SDLK_LESS:			return	Key_LESS;			break;
	case SDLK_EQUALS:		return	Key_EQUALS;			break;
	case SDLK_GREATER:		return	Key_GREATER;		break;
	case SDLK_QUESTION:		return	Key_QUESTION;		break;
	case SDLK_AT:			return	Key_AT;				break;
	case SDLK_LEFTBRACKET:	return	Key_LEFTBRACKET;	break;
	case SDLK_BACKSLASH:	return	Key_BACKSLASH;		break;
	case SDLK_RIGHTBRACKET: return	Key_RIGHTBRACKET;	break;
	case SDLK_CARET:		return	Key_CARET;			break;
	case SDLK_UNDERSCORE:	return	Key_UNDERSCORE;		break;
	case SDLK_BACKQUOTE:	return	Key_BACKQUOTE;		break;
	case SDLK_a:			return	Key_a;				break;
	case SDLK_b:			return	Key_b;				break;
	case SDLK_c:			return	Key_c;				break;
	case SDLK_d:			return	Key_d;				break;
	case SDLK_e:			return	Key_e;				break;
	case SDLK_f:			return	Key_f;				break;
	case SDLK_g:			return	Key_g;				break;
	case SDLK_h:			return	Key_h;				break;
	case SDLK_i:			return	Key_i;				break;
	case SDLK_j:			return	Key_j;				break;
	case SDLK_k:			return	Key_k;				break;
	case SDLK_l:			return	Key_l;				break;
	case SDLK_m:			return	Key_m;				break;
	case SDLK_n:			return	Key_n;				break;
	case SDLK_o:			return	Key_o;				break;
	case SDLK_p:			return	Key_p;				break;
	case SDLK_q:			return	Key_q;				break;
	case SDLK_r:			return	Key_r;				break;
	case SDLK_s:			return	Key_s;				break;
	case SDLK_t:			return	Key_t;				break;
	case SDLK_u:			return	Key_u;				break;
	case SDLK_v:			return	Key_v;				break;
	case SDLK_w:			return	Key_w;				break;
	case SDLK_x:			return	Key_x;				break;
	case SDLK_y:			return	Key_y;				break;
	case SDLK_z:			return	Key_z;				break;

	//\\ Add new Command* to return for custom Input Library Events here

	default: break;
	}

	//* Controller
	if (evt == EventListener::Event::BUTTON_INVALID) {			return BUTTON_INVALID; }
	if (evt == EventListener::Event::BUTTON_A) {				return BUTTON_A; }
	if (evt == EventListener::Event::BUTTON_B) {				return BUTTON_B; }
	if (evt == EventListener::Event::BUTTON_X) {				return BUTTON_X; }
	if (evt == EventListener::Event::BUTTON_Y) {				return BUTTON_Y; }
	if (evt == EventListener::Event::BUTTON_BACK) {				return BUTTON_BACK; }
	if (evt == EventListener::Event::BUTTON_GUIDE) {			return BUTTON_GUIDE; }
	if (evt == EventListener::Event::BUTTON_START) {			return BUTTON_START; }
	if (evt == EventListener::Event::BUTTON_LEFTSTICK) {		return BUTTON_LEFTSTICK; }
	if (evt == EventListener::Event::BUTTON_RIGHTSTICK) {		return BUTTON_RIGHTSTICK; }
	if (evt == EventListener::Event::BUTTON_LEFTSHOULDER) {		return BUTTON_LEFTSHOULDER; }
	if (evt == EventListener::Event::BUTTON_RIGHTSHOULDER) {	return BUTTON_RIGHTSHOULDER; }
	if (evt == EventListener::Event::BUTTON_DPAD_UP) {			return BUTTON_DPAD_UP; }
	if (evt == EventListener::Event::BUTTON_DPAD_DOWN) {		return BUTTON_DPAD_DOWN; }
	if (evt == EventListener::Event::BUTTON_DPAD_LEFT) {		return BUTTON_DPAD_LEFT; }
	if (evt == EventListener::Event::BUTTON_DPAD_RIGHT) {		return BUTTON_DPAD_RIGHT; }
}

//* Required to update the input
void InputManager::ProcessInput()
{
	//* New Input Library Event
	SDL_Event evn;

	//* New Event Listener Type
	EventListener::Type type;

	while (SDL_PollEvent(&evn) != 0)
	{
		//* Print Key Code on Press
		if (evn.type == SDL_KEYDOWN) { std::cout << evn.key.keysym.sym << std::endl; }
		else if (evn.type == SDL_CONTROLLERBUTTONDOWN)  {  std::cout << std::to_string(evn.cbutton.button) << std::endl;  }


		//* Get Event Listener Type
		switch (evn.type)
		{
		case SDL_KEYDOWN: type = EventListener::Type::Press;	break;
		case SDL_KEYUP: type = EventListener::Type::Release;	break;

		default: type = EventListener::Type::None;				break;
		}

		//* Get Key Event and call Input Manager Dispatch for that key
		switch (evn.key.keysym.sym)
		{
		case SDLK_UNKNOWN:		Dispatch(type, EventListener::Event::UNKNOWN);			break;
		case SDLK_RETURN:		Dispatch(type, EventListener::Event::RETURN);			break;
		case SDLK_ESCAPE:		Dispatch(type, EventListener::Event::ESCAPE);			break;
		case SDLK_BACKSPACE:	Dispatch(type, EventListener::Event::BACKSPACE);		break;
		case SDLK_TAB:			Dispatch(type, EventListener::Event::TAB);				break;
		case SDLK_SPACE:		Dispatch(type, EventListener::Event::SPACE);			break;
		case SDLK_EXCLAIM:		Dispatch(type, EventListener::Event::EXCLAIM);			break;
		case SDLK_QUOTEDBL:		Dispatch(type, EventListener::Event::QUOTEDBL);			break;
		case SDLK_HASH:			Dispatch(type, EventListener::Event::HASH);				break;
		case SDLK_PERCENT:		Dispatch(type, EventListener::Event::PERCENT);			break;
		case SDLK_DOLLAR:		Dispatch(type, EventListener::Event::DOLLAR);			break;
		case SDLK_AMPERSAND:	Dispatch(type, EventListener::Event::AMPERSAND);		break;
		case SDLK_QUOTE:		Dispatch(type, EventListener::Event::QUOTE);			break;
		case SDLK_LEFTPAREN:	Dispatch(type, EventListener::Event::LEFTPAREN);		break;
		case SDLK_RIGHTPAREN:	Dispatch(type, EventListener::Event::RIGHTPAREN);		break;
		case SDLK_ASTERISK:		Dispatch(type, EventListener::Event::ASTERISK);			break;
		case SDLK_PLUS:			Dispatch(type, EventListener::Event::PLUS);				break;
		case SDLK_COMMA:		Dispatch(type, EventListener::Event::COMMA);			break;
		case SDLK_MINUS:		Dispatch(type, EventListener::Event::MINUS);			break;
		case SDLK_PERIOD:		Dispatch(type, EventListener::Event::PERIOD);			break;
		case SDLK_SLASH:		Dispatch(type, EventListener::Event::SLASH);			break;
		case SDLK_0:			Dispatch(type, EventListener::Event::NUM_0);			break;
		case SDLK_1:			Dispatch(type, EventListener::Event::NUM_1);			break;
		case SDLK_2:			Dispatch(type, EventListener::Event::NUM_2);			break;
		case SDLK_3:			Dispatch(type, EventListener::Event::NUM_3);			break;
		case SDLK_4:			Dispatch(type, EventListener::Event::NUM_4);			break;
		case SDLK_5:			Dispatch(type, EventListener::Event::NUM_5);			break;
		case SDLK_6:			Dispatch(type, EventListener::Event::NUM_6);			break;
		case SDLK_7:			Dispatch(type, EventListener::Event::NUM_7);			break;
		case SDLK_8:			Dispatch(type, EventListener::Event::NUM_8);			break;
		case SDLK_9:			Dispatch(type, EventListener::Event::NUM_9);			break;
		case SDLK_COLON:		Dispatch(type, EventListener::Event::COLON);			break;
		case SDLK_SEMICOLON:	Dispatch(type, EventListener::Event::SEMICOLON);		break;
		case SDLK_LESS:			Dispatch(type, EventListener::Event::LESS);				break;
		case SDLK_EQUALS:		Dispatch(type, EventListener::Event::EQUALS);			break;
		case SDLK_GREATER:		Dispatch(type, EventListener::Event::GREATER);			break;
		case SDLK_QUESTION:		Dispatch(type, EventListener::Event::QUESTION);			break;
		case SDLK_AT:			Dispatch(type, EventListener::Event::AT);				break;
		case SDLK_LEFTBRACKET:	Dispatch(type, EventListener::Event::LEFTBRACKET);		break;
		case SDLK_BACKSLASH:	Dispatch(type, EventListener::Event::BACKSLASH);		break;
		case SDLK_RIGHTBRACKET: Dispatch(type, EventListener::Event::RIGHTBRACKET);		break;
		case SDLK_CARET:		Dispatch(type, EventListener::Event::CARET);			break;
		case SDLK_UNDERSCORE:	Dispatch(type, EventListener::Event::UNDERSCORE);		break;
		case SDLK_BACKQUOTE:	Dispatch(type, EventListener::Event::BACKQUOTE);		break;
		case SDLK_a:			Dispatch(type, EventListener::Event::a);				break;
		case SDLK_b:			Dispatch(type, EventListener::Event::b);				break;
		case SDLK_c:			Dispatch(type, EventListener::Event::c);				break;
		case SDLK_d:			Dispatch(type, EventListener::Event::d);				break;
		case SDLK_e:			Dispatch(type, EventListener::Event::e);				break;
		case SDLK_f:			Dispatch(type, EventListener::Event::f);				break;
		case SDLK_g:			Dispatch(type, EventListener::Event::g);				break;
		case SDLK_h:			Dispatch(type, EventListener::Event::h);				break;
		case SDLK_i:			Dispatch(type, EventListener::Event::i);				break;
		case SDLK_j:			Dispatch(type, EventListener::Event::j);				break;
		case SDLK_k:			Dispatch(type, EventListener::Event::k);				break;
		case SDLK_l:			Dispatch(type, EventListener::Event::l);				break;
		case SDLK_m:			Dispatch(type, EventListener::Event::m);				break;
		case SDLK_n:			Dispatch(type, EventListener::Event::n);				break;
		case SDLK_o:			Dispatch(type, EventListener::Event::o);				break;
		case SDLK_p:			Dispatch(type, EventListener::Event::p);				break;
		case SDLK_q:			Dispatch(type, EventListener::Event::q);				break;
		case SDLK_r:			Dispatch(type, EventListener::Event::r);				break;
		case SDLK_s:			Dispatch(type, EventListener::Event::s);				break;
		case SDLK_t:			Dispatch(type, EventListener::Event::t);				break;
		case SDLK_u:			Dispatch(type, EventListener::Event::u);				break;
		case SDLK_v:			Dispatch(type, EventListener::Event::v);				break;
		case SDLK_w:			Dispatch(type, EventListener::Event::w);				break;
		case SDLK_x:			Dispatch(type, EventListener::Event::x);				break;
		case SDLK_y:			Dispatch(type, EventListener::Event::y);				break;
		case SDLK_z:			Dispatch(type, EventListener::Event::z);				break;

		default: break;
		}


		//* Controller
		//* Get Event Listener Type
		switch (evn.type)
		{
			//* Controller
		case SDL_CONTROLLERBUTTONDOWN: type = EventListener::Type::Press;	mIsPressed = true;  break;
		case SDL_CONTROLLERBUTTONUP: type = EventListener::Type::Release;	mIsPressed = false; break;
		case SDL_CONTROLLERDEVICEADDED: AddController(evn.cdevice.which);	break;
		case SDL_CONTROLLERDEVICEREMOVED: RemoveController(evn.cdevice.which); break;

		default: type = EventListener::Type::None;				break;
		}

		//* Controller is connected
		if (mIsConnected)
		{
			if (evn.type == SDL_CONTROLLERBUTTONDOWN)
			{
				type = EventListener::Type::Press;
				if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_INVALID) {				mControllerButton = EventListener::Event::BUTTON_INVALID; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_A) {				mControllerButton = EventListener::Event::BUTTON_A; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_B) {				mControllerButton = EventListener::Event::BUTTON_B; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_X) {				mControllerButton = EventListener::Event::BUTTON_X; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {				mControllerButton = EventListener::Event::BUTTON_Y; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_BACK) {			mControllerButton = EventListener::Event::BUTTON_BACK; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_GUIDE) {			mControllerButton = EventListener::Event::BUTTON_GUIDE; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_START) {			mControllerButton = EventListener::Event::BUTTON_START; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSTICK) {		mControllerButton = EventListener::Event::BUTTON_LEFTSTICK; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSTICK) {		mControllerButton = EventListener::Event::BUTTON_RIGHTSTICK; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER) {	mControllerButton = EventListener::Event::BUTTON_LEFTSHOULDER; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) {	mControllerButton = EventListener::Event::BUTTON_RIGHTSHOULDER; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) {			mControllerButton = EventListener::Event::BUTTON_DPAD_UP; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {		mControllerButton = EventListener::Event::BUTTON_DPAD_DOWN; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {		mControllerButton = EventListener::Event::BUTTON_DPAD_LEFT; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {		mControllerButton = EventListener::Event::BUTTON_DPAD_RIGHT; }
				controllerHeld[mControllerButton] = true;
				Dispatch(type, mControllerButton);
				countedFrames = 0;
			}

			else if (evn.type == SDL_CONTROLLERBUTTONUP)
			{
				type = EventListener::Type::Release;
				if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_INVALID) { mControllerButton = EventListener::Event::BUTTON_INVALID; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_A) { mControllerButton = EventListener::Event::BUTTON_A; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_B) { mControllerButton = EventListener::Event::BUTTON_B; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_X) { mControllerButton = EventListener::Event::BUTTON_X; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_Y) { mControllerButton = EventListener::Event::BUTTON_Y; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_BACK) { mControllerButton = EventListener::Event::BUTTON_BACK; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_GUIDE) { mControllerButton = EventListener::Event::BUTTON_GUIDE; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_START) { mControllerButton = EventListener::Event::BUTTON_START; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSTICK) { mControllerButton = EventListener::Event::BUTTON_LEFTSTICK; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSTICK) { mControllerButton = EventListener::Event::BUTTON_RIGHTSTICK; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER) { mControllerButton = EventListener::Event::BUTTON_LEFTSHOULDER; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) { mControllerButton = EventListener::Event::BUTTON_RIGHTSHOULDER; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) { mControllerButton = EventListener::Event::BUTTON_DPAD_UP; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) { mControllerButton = EventListener::Event::BUTTON_DPAD_DOWN; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) { mControllerButton = EventListener::Event::BUTTON_DPAD_LEFT; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) { mControllerButton = EventListener::Event::BUTTON_DPAD_RIGHT; }
				controllerHeld[mControllerButton] = false;
				Dispatch(type, mControllerButton);
				countedFrames = 0;
			}


			//* Joystick
			//* Get If Axis Is Moving
			if (evn.type == SDL_JOYAXISMOTION)
			{
				//* Left Stick X Axis
				if (evn.jaxis.axis == 0) { Stick_Left_X = evn.jaxis.value; }

				//* Left Stick Y Axis
				if (evn.jaxis.axis == 1) { Stick_Left_Y = evn.jaxis.value; }

				//* Left Trigger Axis
				if (evn.jaxis.axis == 2)
				{
					Stick_Left_T = evn.jaxis.value;
					std::cout << "Left T : " << Stick_Left_T << std::endl;
				}

				//* Right Stick X Axis
				if (evn.jaxis.axis == 3){ Stick_Right_X = evn.jaxis.value; }

				//* Right Stick Y Axis
				if (evn.jaxis.axis == 4) { Stick_Right_Y = evn.jaxis.value; }

				//* Right Trigger Axis
				if (evn.jaxis.axis == 5)
				{
					Stick_Right_T = evn.jaxis.value;
					std::cout << "Right T : " << Stick_Right_X << std::endl;
				}
			}
		}


		//\\ Add new Input Library Events here for custom detection

	}

	//* Controller Hold Update
	countedFrames++;
	if (countedFrames > controllerDelay)
	{
		for (auto const &button : controllerHeld)
		{
			if (button.second) { Dispatch(EventListener::Type::Hold, button.first); }
			else
			{
				controllerHeld[button.first] = false;
			}
		}
		countedFrames = 0;
	}

	std::cout << getLeftStickVector().x << "\t" << getLeftStickVector().y << std::endl;
	//std::cout << Vector2f(Stick_Left_X, Stick_Left_Y).magnitude() << std::endl;
}

//* Add Contoller if Detected
void InputManager::AddController(int id)
{
	if (SDL_IsGameController(id)) 
	{
		mGameController = SDL_GameControllerOpen(id);
		std::cout << SDL_GameControllerMapping(mGameController) << std::endl;
		mIsConnected = true;

		if (mGameController) 
		{
			mJoyStick = SDL_JoystickOpen(id);
			int instanceID = SDL_JoystickInstanceID(mJoyStick);
		}
	}
}

//* Disconnect Controller
void InputManager::RemoveController(int id)
{
	SDL_GameControllerClose(mGameController);
	mIsConnected = false;
}

//* Set Delay of Controller Update
void InputManager::SetControllerDelay(int delay)
{
	controllerDelay = delay;
}

//* Return X, Y for Left Stick Vector
Vector2f InputManager::getLeftStickVector()
{
	if (Vector2f(Stick_Left_X, Stick_Left_Y).magnitude() > Stick_Dead_Zone)
	{
		return Vector2f(Stick_Left_X, Stick_Left_Y);
	}
	else
	{
		return Vector2f(0, 0);
	}
}

//* Return X, Y for Left Stick Angle
float InputManager::getLeftStickAngle()
{
	return (180 - (180 * (atan2(Stick_Left_X, Stick_Left_Y)) / M_PI));
}

//* Return X, Y for Right Stick
Vector2f InputManager::getRightStickVector()
{
	if (Vector2f(Stick_Right_X, Stick_Right_Y).magnitude() > Stick_Dead_Zone)
	{
		return Vector2f(Stick_Right_X, Stick_Right_Y);
	}
	else
	{
		return Vector2f(0, 0);
	}
}

//* Return X, Y for Right Stick Angle
float InputManager::getRightStickAngle()
{
	return (180 - (180 * (atan2(Stick_Right_X, Stick_Right_Y)) / M_PI));
}


