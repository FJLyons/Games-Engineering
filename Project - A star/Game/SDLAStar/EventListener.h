#pragma once

/**Used as an interface for the event dispatcher*/
/*Objects wanting to receive events must inherit from this*/

class EventListener
{
public:

	//list of possible events
	//add your own events here
	enum Event {
		SPACE	,
		QUIT	,
		ANYKEY
	};


	virtual void onEvent(Event)=0;
};

