#pragma once
#include <queue>
#include "Command.h"

class CommandQueue
{
public:

	Command Pop()
	{
		Command result = mQueue.front();
		mQueue.pop();
		return result;
	}
	
	Command Top()
	{
		return mQueue.front();
	}

	void Push(const Command& command)
	{
		mQueue.push(command);
	}

	bool isEmpty()
	{
		return mQueue.empty();
	}
private:
	std::queue<Command> mQueue; 
};

