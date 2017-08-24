#pragma once
#include <memory>
#include <SFML\System\Time.hpp>
#include <SFML\Window.hpp>
#include "Context.h"

class StateStack;

struct StateCreationParam
{
	StateCreationParam() {}
	virtual ~StateCreationParam() {}
};

struct GameOverParam: public StateCreationParam
{
	GameOverParam(RecieverType type): mType(type) {}
	virtual ~GameOverParam() {}
	RecieverType mType;
};

typedef std::unique_ptr<StateCreationParam> state_param_ptr;

enum class ID{None,
	Game,
	Title,
	MainMenu,
	Pause,
	GameOver
};

class State
{
public:
	typedef  std::unique_ptr<State> Ptr;

	State(StateStack& stack, Context context, state_param_ptr param = state_param_ptr(nullptr) ):mStack(&stack), mContext(context), mStateParam(std::move(param)){}
	virtual ~State();

	virtual void		draw() = 0;
	virtual bool		update(sf::Time dt) = 0;
	virtual bool		handleEvent(const sf::Event& event) = 0;
protected:
	void				requestStackPush(ID stateID, state_param_ptr param = state_param_ptr(nullptr));
	void				requestStackPop();
	void				requestStateCLear();

	Context				getContext() const;
	void				setBackGround(sf::Texture*);
	sf::Texture*		getTexture();
	void				renderBackGround(sf::RenderWindow& window);
	virtual void		handleParameter() = 0;
	state_param_ptr		mStateParam;
private:
	StateStack*			mStack;
	Context				mContext;
	//
	sf::Texture*		mTexture;
	//
	
};