#pragma once
#include "SBTAbstractApplicationState.h"
#include "World.h"
#include "Player.h"

class GameState: public SBTAbstractApplicationState
{
public:
	GameState(SBTStateStack& stack, SBTContext context, state_param_ptr param = state_param_ptr(nullptr) );
	~GameState(){}

	void			draw();
	
	bool			update(sf::Time dt);
	
	bool			handleEvent(const sf::Event& event);
private:
	Player*			mPlayer;
	World			mWorld;
};

