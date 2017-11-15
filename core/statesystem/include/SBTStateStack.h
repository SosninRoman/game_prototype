#pragma once
#include <vector>
#include <map>
#include <functional>
#include "SBTAbstractApplicationState.h"
#include "SBTContext.h"
#include <memory>

template<class T>
class StateCreator
{
public:
	StateCreator(SBTStateStack& stack, SBTContext context): stack(&stack), context(context){}
	SBTAbstractApplicationState::Ptr operator() (state_param_ptr param){return SBTAbstractApplicationState::Ptr(new T(*stack, context, move(param) ));}
private:
    SBTStateStack* stack;
	SBTContext context;
};


class SBTStateStack
{
public:
	enum Action{Push, Pop, Clear};

    SBTStateStack(const SBTContext& context):mContext(context){}
	~SBTStateStack() = default;

	template<class T>
	void registerState(int stateID);

	void									pushState(int stateID, state_param_ptr&& param = state_param_ptr(nullptr) );
	void									popState();
	void									clearState();

	void									update(sf::Time dt);
	void									draw();
	void									handleEvent(sf::Event& event);

	bool									isEmpty() const {return mStack.empty();}
private:
	struct PendingChange
	{
		Action action;
		int stateID;
		state_param_ptr param;

		explicit PendingChange(Action action, int id = 0, state_param_ptr param = state_param_ptr(nullptr) ):
				action(action), stateID(id), param(std::move(param))
		{

		}

		PendingChange(PendingChange&& rhs):action(rhs.action), stateID(rhs.stateID), param(move(rhs.param))
        {

        }
	};

	SBTAbstractApplicationState::Ptr													createState(int dtateID, state_param_ptr param = state_param_ptr(nullptr) );
	void														applyPendingChanges();

	SBTContext														mContext;
	std::vector<SBTAbstractApplicationState::Ptr>										mStack;
	std::vector<PendingChange>									mPendingChanges;
	std::map<int,std::function<SBTAbstractApplicationState::Ptr(state_param_ptr)> >	mStatesFactory;
};

template<class T>
void SBTStateStack::registerState(int stateID)
{
	mStatesFactory[stateID] = StateCreator<T>(*this, mContext);
}