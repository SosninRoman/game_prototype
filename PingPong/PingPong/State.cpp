#include "State.h"
#include "StateStack.h"

State::~State()
{
	
}

void State::requestStackPush(ID stateID)
{
	mStack->pushState(stateID);
}

void State::requestStackPop()
{
	mStack->popState();
}

void State::requestStateCLear()
{
	mStack->clearState();
}

Context State::getContext() const
{
	return mContext;
}