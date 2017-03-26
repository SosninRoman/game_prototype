#pragma once
#include <vector>
#include <map>
#include <functional>
#include "State.h"
#include "Context.h"

template<class T>
class StateCreator
{
public:
	StateCreator(StateStack& stack, Context context): stack(&stack), context(context){}
	State::Ptr operator() (){return State::Ptr(new T(*stack, context));}
private:
	StateStack* stack;
	Context context;
};


class StateStack
{
public:
	enum Action{Push, Pop, Clear};

	StateStack(Context context):mContext(context){}
	~StateStack();

	template<class T>
	void registerState(ID stateID);

	void pushState(ID stateID);
	void popState();
	void clearState();

	void update(sf::Time dt);
	void draw();
	void handleEvent(sf::Event& event);

	bool isEmpty() const {return mStack.empty();}
private:
	struct PendingChange
	{
		Action action;
		ID stateID;
		PendingChange(Action action, ID id = None):action(action), stateID(id){}
	};

	State::Ptr createState(ID dtateID);
	void applyPendingChanges();

	Context                                    mContext;
	std::vector<State::Ptr>                    mStack;
	std::vector<PendingChange>                 mPendingChanges;
	std::map<ID,std::function<State::Ptr()> > mStatesFactory;
};

template<class T>
void StateStack::registerState(ID stateID)
{
	mStatesFactory[stateID] = StateCreator<T>(*this, mContext);
}