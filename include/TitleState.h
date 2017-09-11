#pragma once
#include "StateStack.h"

class TitleState: public State
{
public:
	TitleState(StateStack& stack, Context context, state_param_ptr param = state_param_ptr(nullptr) );
	~TitleState(){}

	void draw();
	
	bool update(sf::Time dt);
	
	virtual bool handleEvent(const sf::Event& event);
private:
	sf::Text mText;

	bool mShow;
	
	sf::Time mTextEffectTime;
};

