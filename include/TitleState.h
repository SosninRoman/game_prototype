#pragma once
#include "SBTStateStack.h"

class TitleState: public SBTAbstractApplicationState
{
public:
	TitleState(SBTStateStack& stack, SBTContext context, state_param_ptr param = state_param_ptr(nullptr) );
	~TitleState(){}

	void draw();
	
	bool update(sf::Time dt);
	
	virtual bool handleEvent(const sf::Event& event);
private:
	sf::Text mText;

	bool mShow;
	
	sf::Time mTextEffectTime;
};

