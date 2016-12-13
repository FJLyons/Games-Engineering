#include "stdafx.h"
#include "Threading.h"

Threading * Threading::_instance = nullptr; // Create singleton

Threading::Threading() : semaphoreTask(SDL_CreateSemaphore(0)), mutexLock(SDL_CreateMutex())
{
}


Threading::~Threading()
{
}

Threading * Threading::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new Threading();
	}
	return _instance;
}

SDL_mutex * Threading::getLock()
{
	return mutexLock;
}

SDL_sem * Threading::getTask()
{
	return semaphoreTask;
}

std::function<void()> Threading::findPaths()
{
	SDL_LockMutex(mutexLock);//

	if (paths.empty())
	{
		return std::function<void*()>();
	}

	auto path = paths.front();
	paths.pop_front();

	SDL_UnlockMutex(mutexLock);//
	return path;
}

void Threading::addTask(std::function<void()> function)
{
	SDL_LockMutex(mutexLock);//
	paths.push_back(function);
	SDL_UnlockMutex(mutexLock);//

	SDL_SemPost(semaphoreTask);
}

void Threading::spawnWorkers()
{
	int numWorkers = std::thread::hardware_concurrency() - 1;

	for (int i = 0; i < numWorkers; i++)
	{
		processThreadPool.push_back(SDL_CreateThread(worker, "Generic Worker", (void*)NULL));
	}
}
