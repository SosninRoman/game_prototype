#include "Paddle.h"
#include "GameData.h"

namespace
{
	const std::vector<PaddleData> Table = initializePaddleData();
}

Paddle::Paddle(RecieverType type , TextureHolder& textures): 
	SBTAbstractSceneNode(), SBTAbstractAnimatedNode(textures), mRecieverType(type)
{
	mType = PaddleType::RightPaddle;
}

void Paddle::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const 
{
	SBTAbstractAnimatedNode::drawCurrent(target, states);
}

int Paddle::getActionType() const
{
	return mRecieverType;
}

int Paddle::getNodeType() const
{
	return NodeType::PaddleNodeType;
}

float Paddle::getSpeed() const
{
	return Table[static_cast<int>(mType)].speed;
}

sf::FloatRect Paddle::getGlobalBounds() const
{
	return SBTAbstractAnimatedNode::getGlobalBounds();
}

void Paddle::updateCurrent(sf::Time dt)
{
	SBTAbstractSceneNode::updateCurrent(dt);
	SBTAbstractAnimatedNode::updateCurrent(dt);
}

void Paddle::centerOrigin()
{
	SBTAbstractAnimatedNode::centerOrigin();
	int a = 1;
}
