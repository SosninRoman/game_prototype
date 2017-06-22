#include "Paddle.h"
#include "GameData.h"

namespace
{
	const std::vector<PaddleData> Table = initializePaddleData();
}

Paddle::Paddle(sf::RectangleShape&rect, RecieverType type , TextureHolder& textures): 
	mRecieverType(type), mAnimator(textures)
{
	mType = PaddleType::RightPaddle;

	auto animation = mAnimator.createAnimation("paddle_up",PaddleTexture,sf::seconds(2),false);
	animation->AddFrames(sf::Vector2i(0,0), sf::Vector2i(25,100),1);
	mAnimator.switchAnimation("paddle_up");

	animation = mAnimator.createAnimation("paddle_down",PaddleTexture,sf::seconds(2),false, true, 180);
	animation->AddFrames(sf::Vector2i(0,0), sf::Vector2i(25,100),1);
	//mAnimator.switchAnimation("paddle_down");
}

void Paddle::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const 
{
	mAnimator.drawCurrent(target, states);
}

RecieverType Paddle::getActionType() const
{
	return mRecieverType;
}

NodeType Paddle::getNodeType() const
{
	return NodeType::Paddle;
}

float Paddle::getSpeed() const
{
	return Table[static_cast<int>(mType)].speed;
}

sf::FloatRect Paddle::getGlobalBounds() const
{
	return getWorldTransform().transformRect(mAnimator.getSprite().getGlobalBounds());
}

void Paddle::updateCurrent(sf::Time dt)
{
	MoveableNode::updateCurrent(dt);
	MoveableNode::setVelocity(0,0);
	mAnimator.update(dt);
}

void Paddle::centerOrigin()
{
	mAnimator.centerOrigin();
}

sf::Vector2u Paddle::getSize()
{
	return mAnimator.getSize();
}