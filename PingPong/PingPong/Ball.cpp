#include "Ball.h"

Ball::Ball(sf::CircleShape& ball):
	mBall(ball)
{
}

void Ball::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const 
{
	target.draw(mBall,states);
}

RecieverType Ball::getActionType() const
{
	return RecieverType::Ball;
}