#include "StateStack.h"
#include <assert.h>

StateStack::~StateStack()
{
}

State::Ptr StateStack::createState(ID stateID)
{
	auto ptr = mStatesFactory.find(stateID);
	assert(ptr != mStatesFactory.end());
	return ptr->second();
}

void StateStack::pushState(ID stateID)
{
	mPendingChanges.push_back(PendingChange(Push, stateID));
}

void StateStack::popState()
{
	mPendingChanges.push_back(PendingChange(Pop));
}

void StateStack::clearState()
{
	mPendingChanges.push_back(PendingChange(Clear));
}

void StateStack::applyPendingChanges()
{
	for(auto tmp = mPendingChanges.begin(); tmp != mPendingChanges.end(); ++tmp)
	{
		switch(tmp->action)
		{
		case Push:
			mStack.push_back(createState(tmp->stateID));
			break;
		case Pop:
			mStack.pop_back();
			break;
		case Clear:
			mStack.clear();
			break;
		}
	}
	mPendingChanges.clear();
}

void StateStack::update(sf::Time dt)
{
	for (auto tmp = mStack.rbegin(); tmp != mStack.rend(); ++tmp)
	{
		if (! (*tmp)->update(dt)) break;
	}
	applyPendingChanges();
}

void StateStack::draw()
{
	for (auto tmp = mStack.begin(); tmp != mStack.end(); ++tmp)
	{
		(*tmp)->draw(); 
	}
}

void StateStack::handleEvent(sf::Event& event)
{
	for (auto tmp = mStack.rbegin(); tmp != mStack.rend(); ++tmp)
	{
		if (! (*tmp)->handleEvent(event)) break;
	}
	applyPendingChanges();
}