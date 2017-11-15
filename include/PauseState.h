#pragma once
#include "SBTAbstractApplicationState.h"
#include <vector>

class PauseState: public SBTAbstractApplicationState
{
public:
	enum OptionNames{BackToPlay, ExitToMenu};

	PauseState(SBTStateStack& stack, SBTContext context, state_param_ptr param = state_param_ptr(nullptr) );
	~PauseState() = default;

	void						draw() final;
	
	bool						update(sf::Time dt) final;
	
	bool						handleEvent(const sf::Event& event) final;

protected:
	
	void						setColorOfText();

private:
	sf::Font					mFont;
	
	std::vector<sf::Text>		mOptions;
	
	int							mActiveOption;
};

