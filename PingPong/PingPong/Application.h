#pragma once
#include <SFML\Graphics.hpp>
#include "StateStack.h"
#include "ResourceHolder.h"

class Application
{
public:
	Application();
	void run();
private:
	void registerStates();
	void update(sf::Time dt);
	void draw();
	void handleInput();
	sf::RenderWindow mWindow;
	StateStack       mStateStack;
	FontHolder       mFontHolder;
};
