#pragma once
#include <memory>
#include <SFML\System\Time.hpp>
#include <SFML\Window.hpp>
#include "SBTContext.h"

class SBTStateStack;

struct StateCreationParam
{
	StateCreationParam() {}
	virtual ~StateCreationParam() {}
};

typedef std::unique_ptr<StateCreationParam> state_param_ptr;

class SBTAbstractApplicationState
{
public:
	typedef  std::unique_ptr<SBTAbstractApplicationState> Ptr;

	SBTAbstractApplicationState(SBTStateStack& stack, SBTContext context, state_param_ptr param = state_param_ptr(nullptr) ):mStack(&stack), mContext(context), mStateParam(std::move(param)){}
	virtual ~SBTAbstractApplicationState();

	virtual void		draw() = 0;
	
	virtual bool		update(sf::Time dt) = 0;
	
	virtual bool		handleEvent(const sf::Event& event) = 0;
protected:
	void				requestStackPush(int stateID, state_param_ptr param = state_param_ptr(nullptr));
	
	void				requestStackPop();
	
	void				requestStateCLear();

	SBTContext				getContext() const;
	
	void				setBackGround(const sf::Texture*);
	
	const sf::Texture*		getTexture();
	
	void				renderBackGround(sf::RenderWindow& window);
	
	state_param_ptr		mStateParam;
private:
	SBTStateStack*			mStack;

	SBTContext				mContext;

	const sf::Texture*		mTexture;
};