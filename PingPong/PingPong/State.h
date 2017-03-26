#pragma once
#include <memory>
#include <SFML\System\Time.hpp>
#include <SFML\Window.hpp>
#include "Context.h"

class StateStack;

enum ID{None,
	Game,
	Title,
	MainMenu
};

class State
{
public:
	typedef  std::unique_ptr<State> Ptr;

	State(StateStack& stack, Context context):mStack(&stack), mContext(context){}
	virtual ~State();

	virtual void draw() = 0;
	virtual bool update(sf::Time dt) = 0;
	virtual bool handleEvent(const sf::Event& event) = 0;
protected:
	void requestStackPush(ID stateID);
	void requestStackPop();
	void requestStateCLear();

	Context getContext() const;
private:
	StateStack* mStack;
	Context mContext;
};