#pragma once
#include "State.h"

class GameState: public State
{
public:
	GameState(StateStack& stack, Context context);
	~GameState(){}

	void draw();
	bool update(sf::Time dt);
	bool handleEvent(const sf::Event& event);
private:
	float ball_direction;
	float ball_size;
	const float pi;
	float ball_velocity;
	float paddle_velocity;
	sf::Vector2f paddle_size;
	sf::CircleShape ball;
	sf::RectangleShape right_puddle, left_puddle;
};

