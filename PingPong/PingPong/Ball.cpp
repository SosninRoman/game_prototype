#include "Ball.h"

Ball::Ball(TextureHolder& textures):
	mAnimator(textures)
{
	auto animation = mAnimator.createAnimation("roll_ball",BallTexture,sf::seconds(2),true);
	animation->AddFrames(sf::Vector2i(0,0), sf::Vector2i(32,32),8);
	mAnimator.switchAnimation("roll_ball");
}

void Ball::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const 
{
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

void Ball::centerOrigin()
{
	auto sz = getSize();
	setOrigin(sf::Vector2f(getSize().x / 2, getSize().y / 2));
}

sf::Vector2u Ball::getSize()
{
	return mAnimator.getSize();
}

sf::FloatRect Ball::getGlobalBounds() const
{
	return getTransform().transformRect( mAnimator.getSprite().getGlobalBounds() );
}