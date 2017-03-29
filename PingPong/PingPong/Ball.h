#pragma once
#include "moveablenode.h"
class Ball :
	public MoveableNode
{
public:
	Ball(sf::CircleShape& ball);
private:
	sf::CircleShape mBall;
};

