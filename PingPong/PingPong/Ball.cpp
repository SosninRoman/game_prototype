#include "Ball.h"

Ball::Ball(sf::CircleShape& ball, TextureHolder& textures):
	mBall(ball), mAnimator(textures)
{
	auto animation = mAnimator.createAnimation("roll_ball",BallTexture,sf::seconds(2),true);
	animation->AddFrames(sf::Vector2i(0,0), sf::Vector2i(32,32),6);
	mAnimator.switchAnimation("roll_ball");
}

void Ball::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const 
{
	//target.draw(mBall,states);
	mAnimator.drawCurrent(target, states);
}

RecieverType Ball::getActionType() const
{
	return RecieverType::Ball;
}

NodeType Ball::getNodeType() const
{
	return NodeType::Ball;
}

void Ball::updateCurrent(sf::Time dt)
{
	MoveableNode::updateCurrent(dt);
	mAnimator.update(dt);
}