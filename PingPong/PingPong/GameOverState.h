#pragma once
#include "State.h"


class GameOverState: public State
{
public:
	enum OptionNames{Restart, ExitToMenu};

	GameOverState(StateStack& stack, Context context, state_param_ptr param = state_param_ptr(nullptr) );
	~GameOverState();

	void						draw();
	bool						update(sf::Time dt);
	bool						handleEvent(const sf::Event& event);
	
	void						handleParameter();

	protected:
	void						setColorOfText();
private:
	sf::Font					mFont;
	std::vector<sf::Text>		mOptions;
	std::vector<sf::Text>		mTextBox;
	int							mActiveOption;
};

