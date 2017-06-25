#include "Paddle.h"
#include "GameData.h"

namespace
{
	const std::vector<PaddleData> Table = initializePaddleData();
}

Paddle::Paddle(RecieverType type , TextureHolder& textures): 
	SceneNode(), AnimatedNode(textures), mRecieverType(type)
{
	mType = PaddleType::RightPaddle;

	/*AnimatedNode::createAnimation("paddle_up",PaddleTexture,sf::seconds(2),false);
	AnimatedNode::addFrames(string("paddle_up"),sf::Vector2i(0,0), sf::Vector2i(25,100),1);
	AnimatedNode::switchAnimation("paddle_up");*/

	/*AnimatedNode::createAnimation("paddle_down",PaddleTexture,sf::seconds(2),false, true, 180);
	AnimatedNode::addFrames(string("paddle_down"), sf::Vector2i(0,0), sf::Vector2i(25,100),1);
	AnimatedNode::switchAnimation("paddle_down");*/
}

void Paddle::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const 
{
	AnimatedNode::drawCurrent(target, states);
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
	//return getWorldTransform().transformRect( getSpriteBounds() );
	return AnimatedNode::getGlobalBounds();
}

void Paddle::updateCurrent(sf::Time dt)
{
	MoveableNode::updateCurrent(dt);
	MoveableNode::setVelocity(0,0);
	AnimatedNode::updateCurrent(dt);
}

void Paddle::centerOrigin()
{
	AnimatedNode::centerOrigin();
	int a = 1;
}
