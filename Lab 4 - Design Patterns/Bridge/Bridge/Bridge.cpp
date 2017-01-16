#include <iostream>
using namespace std;

// Handle - allows different systems to talk to each other (enabler for Entity Component System patten)
class Character
{
public:
	Character() { }
	void Print() { cout << "Printing Character" << endl; }
	virtual void Draw() {};
};

class HandleToCharacter
{
public:
	HandleToCharacter() : character(new Character()) {  }
	Character* operator->() {
		return character;
	} //overloaded ->

private:
	Character* character;
};

// Abstraction / Interface and Implementation
class DrawAPI
{
public:
	virtual void Draw() = 0;
};

class DrawImpl : public DrawAPI
{
public:
	void Draw() override {
		cout << "Draw Impl" << endl;
	}
};

// Refinement and Implementer
class Player : public Character
{
public:
	Player(DrawAPI* api) { this->api = api; }
	void Draw() override { 
		api->Draw(); 
	}

private:
	DrawAPI* api;
};

int main(void)
{
	HandleToCharacter handle;
	handle->Print();

	DrawAPI* api = new DrawImpl();
	Character* character = new Player(api);
	character->Draw();
	cin.get();
}
