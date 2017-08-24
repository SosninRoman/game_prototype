#include "StateStack.h"
#include <assert.h>

StateStack::~StateStack()
{
}

//States managament

State::Ptr StateStack::createState(ID stateID, state_param_ptr param)
{
	auto ptr = mStatesFactory.find(stateID);
	assert(ptr != mStatesFactory.end());
	return ptr->second(std::move(param) );
}

void StateStack::pushState(ID stateID, state_param_ptr param)
{
	mPendingChanges.push_back(PendingChange(Push, stateID, std::move(param) ) );
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
			mStack.push_back(createState(tmp->stateID, std::move(tmp->param) ) );
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

//Game loop

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