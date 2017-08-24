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
	State::Ptr operator() (state_param_ptr param){return State::Ptr(new T(*stack, context, move(param) ));}
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

	void														pushState(ID stateID, state_param_ptr param = state_param_ptr(nullptr) );
	void														popState();
	void														clearState();

	void														update(sf::Time dt);
	void														draw();
	void														handleEvent(sf::Event& event);

	bool														isEmpty() const {return mStack.empty();}
private:
	struct PendingChange
	{
		Action action;
		ID stateID;
		state_param_ptr param;
		PendingChange(Action action, ID id = ID::None, state_param_ptr param = state_param_ptr(nullptr) ):action(action), stateID(id), param(std::move(param)){}
		PendingChange(PendingChange& rhs):action(rhs.action), stateID(rhs.stateID), param(std::move(rhs.param)){}
	};

	State::Ptr													createState(ID dtateID, state_param_ptr param = state_param_ptr(nullptr) );
	void														applyPendingChanges();

	Context														mContext;
	std::vector<State::Ptr>										mStack;
	std::vector<PendingChange>									mPendingChanges;
	std::map<ID,std::function<State::Ptr(state_param_ptr)> >	mStatesFactory;
};

template<class T>
void StateStack::registerState(ID stateID)
{
	mStatesFactory[stateID] = StateCreator<T>(*this, mContext);
}