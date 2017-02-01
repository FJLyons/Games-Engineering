// Needed for circular dependancy
class GameObject;
class Falling;
class Waiting;
class Jumping;
class Walking;

class State
{
public:
	virtual ~State() {}
	virtual void Update(GameObject& object) {}
};

class GameObject
{
public:
	GameObject(State* state) : m_state(state) {}

	void Update()
	{
		m_state->Update(*this);
	}

	void SetState(State * state)
	{
		if (state != nullptr)
		{
			delete m_state;
			m_state = state;
		}
	}

private:
	State* m_state;
};

class Falling : public State
{
public:
	void Update(GameObject& object);
};

class Jumping : public State
{
public:
	void Update(GameObject& object) override
	{
		std::cout << "Jumping\t";
		object.SetState(new Falling());
	}
};

class Walking : public State
{
public:
	void Update(GameObject& object) override
	{
		std::cout << "Walking\t";
		object.SetState(new Jumping());
	}
};

class Waiting : public State
{
public:
	void Update(GameObject& object) override
	{
		std::cout << "Waiting\t";
		object.SetState(new Walking());
	}
};