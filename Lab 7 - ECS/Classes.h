#include<map>
#include <vector>

enum Type {
	Health
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

	void AddComponent(Type t, Component* c) 
	{ 
		if (components.find(t) == components.end())
		{
			components[t] = new std::vector<Component*>();
		}

		components[t]->push_back(c); 
	}

	//void RemoveComponent(Component* c) { components.erase(std::find(components.begin(), components.end(), c)); }
	std::map<Type, std::vector<Component*>*> GetComponents() { return components; };

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
		std::cout << "HealthSystem Update" << std::endl;
		for (int i = 0; i < entities.size() && entities[i].GetComponents().size() > 0; i++)
		{
			if (entities[i].GetComponents().find(Health) != entities[i].GetComponents().end())
			{
				for (auto const &entityComponent : *entities[i].GetComponents()[Health])
				{
					entityComponent->Update();
				}
			}
		}
	}
};