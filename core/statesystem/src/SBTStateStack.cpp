#include "SBTStateStack.h"
#include <assert.h>

//States managament

SBTAbstractApplicationState::Ptr SBTStateStack::createState(int stateID, state_param_ptr param)
{
	auto ptr = mStatesFactory.find(stateID);
	assert(ptr != mStatesFactory.end());
	return ptr->second(std::move(param) );
}

void SBTStateStack::pushState(int stateID, state_param_ptr&& param)
{
	mPendingChanges.emplace_back(PendingChange(Push, stateID, std::move(param) ) );
}

void SBTStateStack::popState()
{
	mPendingChanges.emplace_back(PendingChange(Pop));
}

void SBTStateStack::clearState()
{
	mPendingChanges.emplace_back(PendingChange(Clear));
}

void SBTStateStack::applyPendingChanges()
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

void SBTStateStack::update(sf::Time dt)
{
	for (auto tmp = mStack.rbegin(); tmp != mStack.rend(); ++tmp)
	{
		if (! (*tmp)->update(dt)) break;
	}
	applyPendingChanges();
}

void SBTStateStack::draw()
{
	for (auto tmp = mStack.begin(); tmp != mStack.end(); ++tmp)
	{
		(*tmp)->draw(); 
	}
}

void SBTStateStack::handleEvent(sf::Event& event)
{
	for (auto tmp = mStack.rbegin(); tmp != mStack.rend(); ++tmp)
	{
		if (! (*tmp)->handleEvent(event)) break;
	}
	applyPendingChanges();
}