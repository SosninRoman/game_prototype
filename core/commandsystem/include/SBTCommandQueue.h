#pragma once
#include <queue>
#include "SBTCommand.h"

class SBTCommandQueue
{
public:

	SBTCommand Pop()
	{
		SBTCommand result = mQueue.front();
		mQueue.pop();
		return result;
	}

	SBTCommand Top()
	{
		return mQueue.front();
	}

	void Push(const SBTCommand& command)
	{
		mQueue.push(command);
	}

	bool isEmpty()
	{
		return mQueue.empty();
	}
private:
	std::queue<SBTCommand> mQueue;
};

