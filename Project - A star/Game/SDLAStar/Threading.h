#pragma once


#include <SDL_mutex.h>
#include <SDL_thread.h>
#include <thread>
#include <queue>

class Threading
{
public:
	Threading();
	~Threading();

public:
	static Threading * getInstance();
	SDL_mutex * getLock();
	SDL_sem * getTask();

	std::function<void()> findPaths();

	void addTask(std::function<void()> function); // Runs the AStar function it is passed

	void spawnWorkers();

private:
	static Threading * _instance;
	SDL_mutex* mutexLock;
	SDL_sem* semaphoreTask;

	std::deque<std::function<void()>> paths;

	std::vector<SDL_Thread*> processThreadPool;
};

static int worker(void* ptr)
{
	srand(time(NULL));
	Threading* threading = Threading::getInstance();
	SDL_mutex* mutlock = threading->getLock();
	SDL_sem* semtask = threading->getTask();

	while (true)
	{
		SDL_SemWait(semtask);
		auto& task = threading->findPaths(); // getting the function
		task(); // calling the function
	}
}
