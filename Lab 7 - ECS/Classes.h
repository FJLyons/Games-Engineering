#include<map>
#include <vector>

enum Type {
	Health,
	Position
};

class Component
{
public:
	Component() {}
	virtual ~Component() {}
	virtual void Update() {}
};

class Entity
{
	int id;
public:
	Entity() {}
	~Entity() {}

	std::map<Type, std::vector<Component*>*> GetComponents() { return components; };

	void AddComponent(Type t, Component* c) 
	{ 
		if (components.find(t) == components.end())
		{
			components[t] = new std::vector<Component*>();
		}

		components[t]->push_back(c); 
	}

	void RemoveComponent(Component* c) { components[Type::Health]->clear(); }

private:
	std::map<Type, std::vector<Component*>*> components;
};

class HealthComponenet : public Component
{
public:
	HealthComponenet() : health(100) {}
	~HealthComponenet() {}

	int GetHealth() { return health; }
	void SetHealth(int h) { health = h; }

private:
	int health;
};

class HealthSystem
{
	std::vector<Entity> entities;

public:
	HealthSystem() {}
	~HealthSystem() {}


	void AddEntity(Entity e) { entities.push_back(e); }
	void Update()
	{
		std::cout << "\nHealthSystem Update\t";
		for (int i = 0; i < entities.size(); i++)
		{
			for (auto const &entityComponent : *entities[i].GetComponents()[Health])
			{
				std::cout << "Health =\t";
				static_cast<HealthComponenet*>(entityComponent)->SetHealth(static_cast<HealthComponenet*>(entityComponent)->GetHealth() + 1);
				std::cout << static_cast<HealthComponenet*>(entityComponent)->GetHealth() << "\t";
			}			
		}
	}
};

class PositionComponenet : public Component
{
public:
	PositionComponenet() : position(100) {}
	~PositionComponenet() {}

	int GetPosition() { return position; }
	void SetPosition(int p) { position = p; }

private:
	int position;
};

class PositionSystem
{
	std::vector<Entity> entities;

public:
	PositionSystem() {}
	~PositionSystem() {}


	void AddEntity(Entity e) { entities.push_back(e); }
	void Update()
	{
		std::cout << "\nPositionSystem Update\t";
		for (int i = 0; i < entities.size(); i++)
		{
			for (auto const &entityComponent : *entities[i].GetComponents()[Position])
			{
				std::cout << "Position =\t";
				static_cast<PositionComponenet*>(entityComponent)->SetPosition(static_cast<PositionComponenet*>(entityComponent)->GetPosition() + 1);
				std::cout << static_cast<PositionComponenet*>(entityComponent)->GetPosition() << "\t";
			}
		}
	}
};