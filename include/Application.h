#pragma once
#include <SFML\Graphics.hpp>
#include "StateStack.h"
#include "ResourceHolder.h"
#include "Player.h"

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
	Player           mPlayer;
	StateStack       mStateStack;
	//resources
	FontHolder       mFontHolder;	
	TextureHolder    mTextureHolder;
};

