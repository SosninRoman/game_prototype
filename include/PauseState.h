#pragma once
#include "State.h"
#include <vector>

class PauseState: public State
{
public:
	enum OptionNames{BackToPlay, ExitToMenu};

	PauseState(StateStack& stack, Context context, state_param_ptr param = state_param_ptr(nullptr) );
	~PauseState();

	void						draw();
	
	bool						update(sf::Time dt);
	
	bool						handleEvent(const sf::Event& event);

protected:
	
	void						setColorOfText();

private:
	sf::Font					mFont;
	
	std::vector<sf::Text>		mOptions;
	
	int							mActiveOption;
};

