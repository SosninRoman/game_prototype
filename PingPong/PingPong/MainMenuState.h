#pragma once
#include "State.h"
#include <vector>

class MainMenuState: public State
{
public:
	enum OptionNames{Play, Exit};

	MainMenuState(StateStack& stack, Context context);
	~MainMenuState(){}

	void draw();
	bool update(sf::Time dt);
	bool handleEvent(const sf::Event& event);
protected:
	void setColorOfText();
private:
	sf::Font mFont;
	std::vector<sf::Text> mOptions;
	int mActiveOption;
};

