#pragma once
#include "State.h"
#include "World.h"

class GameState: public State
{
public:
	GameState(StateStack& stack, Context context);
	~GameState(){}

	void draw();
	bool update(sf::Time dt);
	bool handleEvent(const sf::Event& event);
private:

	World mWorld;
};

