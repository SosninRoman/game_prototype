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
