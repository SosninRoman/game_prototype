#include "Paddle.h"
#include "GameData.h"

namespace
{
	const std::vector<PaddleData> Table = initializePaddleData();
}

void Paddle::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const 
{
	target.draw(mRect, states);
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