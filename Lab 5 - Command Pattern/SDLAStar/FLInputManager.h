#pragma once
#include "SDL.h"

#include<map>
#include<vector>
#include<iostream>
#include<queue>
#include<thread>
#include<functional>

//* Abstract class for input keys
class EventListener
{
public:
	//list of possible events
	//add your own events here
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
	};

	virtual void onEvent(Event) = 0;
};

//* Abstract class for input commands
class Command
{
public:
	Command(std::function<void()> function) : m_function(function) {}
	std::function<void()> m_function;
	virtual ~Command() {}
	virtual void execute() = 0;
};

//* Over ride command object with custom command
class OverRideCommand : public Command
{
public:
	OverRideCommand(std::function<void()> function) : Command(function) {}
	virtual void execute()
	{
		m_function();
	}
};

class InputManager
{
	//dictionary holding a list of litener objs for each event type
	std::map<EventListener::Event, std::vector<EventListener*>*> listeners; //pointer to vec of eventlisteners

	// Instance Variables
public:
	static InputManager* getInstance();
private:
	static InputManager* inputManagerInstance;

public:
	InputManager();
	~InputManager();

	void AddListener(EventListener::Event, EventListener*);
	void Dispatch(EventListener::Event);
	
	void ProcessInput();

public:
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
	// Skip uppercase letters
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
};