#pragma once
#include "State.h"
#include "World.h"
#include "Player.h"

class GameState: public State
{
public:
	GameState(StateStack& stack, Context context, state_param_ptr param = state_param_ptr(nullptr) );
	~GameState(){}

	void			draw();
	bool			update(sf::Time dt);
	bool			handleEvent(const sf::Event& event);
	void			handleParameter(){}
private:
	Player&			mPlayer;
	World			mWorld;
};

