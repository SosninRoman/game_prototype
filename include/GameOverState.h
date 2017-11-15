#pragma once
#include "SBTAbstractApplicationState.h"


class GameOverState: public SBTAbstractApplicationState
{
public:
	enum OptionNames{Restart, ExitToMenu};

	GameOverState(SBTStateStack& stack, SBTContext context, state_param_ptr param = state_param_ptr(nullptr) );
	~GameOverState();

	void						draw();
	
	bool						update(sf::Time dt);
	
	bool						handleEvent(const sf::Event& event);
	
protected:
	void						setColorOfText();

private:
	sf::Font					mFont;
	std::vector<sf::Text>		mOptions;
	std::vector<sf::Text>		mTextBox;
	int							mActiveOption;
};

