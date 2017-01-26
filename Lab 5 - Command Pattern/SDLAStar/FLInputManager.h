#pragma once
#include "SDL.h"
#include "LTimer.h"

#include <iostream>
#include <string>
#include<map>
#include<vector>
#include<iostream>
#include<queue>
#include<thread>
#include<functional>

//* Vector2f Class for JoyStick value
class Vector2f
{
public:
	Vector2f(float _x, float _y) : x(_x), y(_y) {}
	Vector2f() : x(0.f), y(0.f) {}

	Vector2f operator*(float m) { x *= m; y *= m; return *this; }
	Vector2f operator+(const Vector2f v) { x += v.x; y += v.y; return *this; }
	float magnitude() { return sqrt(x * x + y * y); }
	float dotProduct(const Vector2f v2){ return (x * v2.x) + (y * v2.y); }

	Vector2f normalise() {
		float TempLength(sqrt((v1.x * v1.x) + (v1.y * v1.y)));
		if (TempLength != 0)
		{
			Vector2f normalised((v1.x / TempLength), (v1.y / TempLength));
			return normalised;
		}
		return Vector2f(0, 0);
	}

	float x;
	float y;
};

//* Abstract class for input keys, input types, mouse and controller.
class EventListener
{
public:
	//* List of possible input events
	enum Event {
		UNKNOWN = 0,

		RETURN = '\r',
		ESCAPE = '\033',
		BACKSPACE = '\b',
		TAB = '\t',
		SPACE = ' ',
		EXCLAIM = '!',
		QUOTEDBL = '"',
		HASH = '#',
		PERCENT = '%',
		DOLLAR = '$',
		AMPERSAND = '&',
		QUOTE = '\'',
		LEFTPAREN = '(',
		RIGHTPAREN = ')',
		ASTERISK = '*',
		PLUS = '+',
		COMMA = ',',
		MINUS = '-',
		PERIOD = '.',
		SLASH = '/',
		NUM_0 = '0',
		NUM_1 = '1',
		NUM_2 = '2',
		NUM_3 = '3',
		NUM_4 = '4',
		NUM_5 = '5',
		NUM_6 = '6',
		NUM_7 = '7',
		NUM_8 = '8',
		NUM_9 = '9',
		COLON = ':',
		SEMICOLON = ';',
		LESS = '<',
		EQUALS = '=',
		GREATER = '>',
		QUESTION = '?',
		AT = '@',
		// Skip uppercase letters
		LEFTBRACKET = '[',
		BACKSLASH = '\\',
		RIGHTBRACKET = ']',
		CARET = '^',
		UNDERSCORE = '_',
		BACKQUOTE = '`',
		a = 'a',
		b = 'b',
		c = 'c',
		d = 'd',
		e = 'e',
		f = 'f',
		g = 'g',
		h = 'h',
		i = 'i',
		j = 'j',
		k = 'k',
		l = 'l',
		m = 'm',
		n = 'n',
		o = 'o',
		p = 'p',
		q = 'q',
		r = 'r',
		s = 's',
		t = 't',
		u = 'u',
		v = 'v',
		w = 'w',
		x = 'x',
		y = 'y',
		z = 'z',
		// Controller
		BUTTON_INVALID = 999,
		BUTTON_A = 1000,
		BUTTON_B,
		BUTTON_X,
		BUTTON_Y,
		BUTTON_BACK,
		BUTTON_GUIDE,
		BUTTON_START,
		BUTTON_LEFTSTICK,
		BUTTON_RIGHTSTICK,
		BUTTON_LEFTSHOULDER,
		BUTTON_RIGHTSHOULDER,
		BUTTON_DPAD_UP,
		BUTTON_DPAD_DOWN,
		BUTTON_DPAD_LEFT,
		BUTTON_DPAD_RIGHT,

		//\\ Add your own events here
	};

	//* List of possible event types
	enum Type {
		Press,
		Release,
		Hold,
		None

		//\\ Add your own events here
	};

	//* Pure virtual function that can be overriden inside any class that inherites from EventListener if needed
	//* Not required to execute keys, ideal for standard event dispatch/ listen procedure for custom events
	virtual void onEvent(Event) = 0;
};

//* Abstract class for input commands
//* Override examples are at the bottom of FLInputManager.h
class Command
{
public:
	//* Constructor for Custom/ once off calls
	Command(std::function<void()> function) : m_function(function) {}
	//* Constructor for Keys with Event Type
	Command(std::function<void()> function, EventListener::Type type) : m_function(function), m_type(type) { m_functions.push_back(m_function); }
	//* Default Destructor
	virtual ~Command() {}

	//* Function Object for executing custom function
	std::function<void()> m_function;
	//* Vector of functions for multiple functions per Key
	std::vector<std::function<void()>> m_functions;
	
	//* Type of Event used to differentiate commands
	EventListener::Type m_type;

	//// Execution calls for firing custom function sent in, based on type
	virtual void execute() {};
	virtual void executePress() {};
	virtual void executeRelease() {};
	virtual void executeHold() {};
};

//* Singleton class for input management
class InputManager
{
public:
	//* Default Constructor
	InputManager();
	//* Default Deconstructor
	~InputManager();

	//// Dictionaries
private:
	//* Dictionary holding a list of litener objects for each event
	std::map<EventListener::Event, std::vector<EventListener*>*> listeners; //* Pointer to vector of EventListeners
	
	//* Dictionary holding a bool for each event
	std::map<EventListener::Event, bool> beingHeld; //* Bool used to detect if the desired Event was previously being held

	//* Dictionary holding a list of command objects for each event
	std::map<EventListener::Event, std::vector<Command*>*> commands; //* Pointer to vector of Commands

	std::map<EventListener::Event, bool> controllerHeld; //* Pointer to vector of Commands

	//// Instance Variables
public:
	//* Used to get the Class Instance
	static InputManager* getInstance();
private:
	//* Used to return the same instance of the Class
	static InputManager* inputManagerInstance;

public:
	//* Required to update the input
	void ProcessInput();

	//* Used to create a key event
	void AddKey(EventListener::Event, Command*, EventListener*);

	//* Input Functions
private:
	//* Create an EventListener object
	void AddListener(EventListener::Event, EventListener*);
	//* Find a specific Event listener in the listeners dictionary, and call its onEvent() function
	void Dispatch(EventListener::Type, EventListener::Event);

	//* Set the hold for a specific Event in the beingHeld dictionary 
	void SetPrevious(EventListener::Event, bool);
	//* Check to see if a specific Event is being held down
	void CheckPrevious(EventListener::Type, EventListener::Event);

	//* Create a Command object
	void AddCommand(EventListener::Event, Command*);
	//* Find a Command object in the commands dictionary, and call its execute function based on Event Type
	void Execute(EventListener::Type, EventListener::Event);

	//* Combine a Command* and an EventListener to work together
	Command*& bindCommand(EventListener::Event);

	//*Controller Variables
private:
	//* Timer
	int countedFrames = 0; 
	int controllerDelay = 1000;

	//* Controller
	SDL_GameController* mGameController = SDL_GameControllerOpen(0); 
	SDL_Joystick* mJoyStick = SDL_JoystickOpen(0);

	EventListener::Event mControllerButton;
	bool mIsConnected = false;
	bool mIsPressed = false;

	//* Add Contoller if Detected
	void AddController(int id);
	//* Disconnect Controller
	void RemoveController(int id);
public:
	//* Set Delay of Controller Update
	void SetControllerDelay(int delayInMilliseconds);

	//* Joy Stick Axis
	int Stick_Dead_Zone = 4000;

	float Stick_Left_X = 0;
	float Stick_Left_Y = 0;
	float Stick_Left_T = 0;
	Vector2f getLeftStickVector();
	float getLeftStickAngle();

	float Stick_Right_X = 0;
	float Stick_Right_Y = 0;
	float Stick_Right_T = 0;
	Vector2f getRightStickVector();
	float getRightStickAngle();

	//// Commands
public:
	// Keys
	Command* Key_UNKNOWN;
	Command* Key_RETURN;
	Command* Key_ESCAPE;
	Command* Key_BACKSPACE;
	Command* Key_TAB;
	Command* Key_SPACE;
	Command* Key_EXCLAIM;
	Command* Key_QUOTEDBL;
	Command* Key_HASH;
	Command* Key_PERCENT;
	Command* Key_DOLLAR;
	Command* Key_AMPERSAND;
	Command* Key_QUOTE;
	Command* Key_LEFTPAREN;
	Command* Key_RIGHTPAREN;
	Command* Key_ASTERISK;
	Command* Key_PLUS;
	Command* Key_COMMA;
	Command* Key_MINUS;
	Command* Key_PERIOD;
	Command* Key_SLASH;
	Command* Key_NUM_0;
	Command* Key_NUM_1;
	Command* Key_NUM_2;
	Command* Key_NUM_3;
	Command* Key_NUM_4;
	Command* Key_NUM_5;
	Command* Key_NUM_6;
	Command* Key_NUM_7;
	Command* Key_NUM_8;
	Command* Key_NUM_9;
	Command* Key_COLON;
	Command* Key_SEMICOLON;
	Command* Key_LESS;
	Command* Key_EQUALS;
	Command* Key_GREATER;
	Command* Key_QUESTION;
	Command* Key_AT;
	Command* Key_LEFTBRACKET;
	Command* Key_BACKSLASH;
	Command* Key_RIGHTBRACKET;
	Command* Key_CARET;
	Command* Key_UNDERSCORE;
	Command* Key_BACKQUOTE;
	Command* Key_a;
	Command* Key_b;
	Command* Key_c;
	Command* Key_d;
	Command* Key_e;
	Command* Key_f;
	Command* Key_g;
	Command* Key_h;
	Command* Key_i;
	Command* Key_j;
	Command* Key_k;
	Command* Key_l;
	Command* Key_m;
	Command* Key_n;
	Command* Key_o;
	Command* Key_p;
	Command* Key_q;
	Command* Key_r;
	Command* Key_s;
	Command* Key_t;
	Command* Key_u;
	Command* Key_v;
	Command* Key_w;
	Command* Key_x;
	Command* Key_y;
	Command* Key_z;
	// Controller
	Command* BUTTON_INVALID;
	Command* BUTTON_A;
	Command* BUTTON_B;
	Command* BUTTON_X;
	Command* BUTTON_Y;
	Command* BUTTON_BACK;
	Command* BUTTON_GUIDE;
	Command* BUTTON_START;
	Command* BUTTON_LEFTSTICK;
	Command* BUTTON_RIGHTSTICK;
	Command* BUTTON_LEFTSHOULDER;
	Command* BUTTON_RIGHTSHOULDER;
	Command* BUTTON_DPAD_UP;
	Command* BUTTON_DPAD_DOWN;
	Command* BUTTON_DPAD_LEFT;
	Command* BUTTON_DPAD_RIGHT;

	//\\ Add new Command* here for custom inputs
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//* Custom Command Override Examples
//* Over ride command object with custom command
class OverRideCommand : public Command
{
public:
	//* Default Constructor sets m_function to function passed in
	OverRideCommand(std::function<void()> function) : Command(function) {}

	//* Run Function sent in, and any other custom operations
	virtual void execute()
	{
		//* Run Function
		m_function();
	}
};

//* Override command object with custom command and type
class OverRideCommandType : public Command
{
public:
	//* Default Constructor sets m_function to function passed in, and m_type to type passed in
	OverRideCommandType(std::function<void()> function, EventListener::Type type) : Command(function, type) {}

	//* Run Function sent in if key is pressed, and any other custom operations
	virtual void executePress()
	{
		//* Loop to find every Key with a Press type
		for (int i = 0; m_type == EventListener::Type::Press && i < m_functions.size(); i++)
		{
			//* Run Function if key is pressed
			m_functions[i]();
		}
	}

	//* Run Function sent in if key is released, and any other custom operations
	virtual void executeRelease()
	{
		//* Loop to find every Key with a Release type
		for (int i = 0; m_type == EventListener::Type::Release && i < m_functions.size(); i++)
		{
			//* Run Function if key is released
			m_functions[i]();
		}
	}

	//* Run Function sent in if key is held, and any other custom operations
	virtual void executeHold()
	{
		//* Loop to find every Key with a Hold type
		for (int i = 0; m_type == EventListener::Type::Hold && i < m_functions.size(); i++)
		{
			//* Run Function if key is held
			m_functions[i]();
		}
	}
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////