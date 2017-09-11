#pragma once
#include <SFML\Graphics.hpp>
#include "StateStack.h"
#include "ResourceHolder.h"
#include "Player.h"
#include "Window.h"

class Application
{
public:
	Application();
	
	void                run();
private:
	void				registerStates();
	
	void				update(sf::Time dt);
	
	void				draw();
	
	void				handleInput();
	
	GameWindow			mWindow;
	
	Player				mPlayer;
	
	StateStack			mStateStack;
	
	//resources
	FontHolder			mFontHolder;	
	
	TextureHolder		mTextureHolder;
};

