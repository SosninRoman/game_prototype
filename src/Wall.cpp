#include "Wall.h"
#include "RecieverTypeEnum.h"

Wall::Wall():
	SBTAbstractSpriteNode(sf::Sprite())
{
}

Wall::~Wall()
{
}

int Wall::getActionType() const
{
	return RecieverType::WallRecieverType;
}

int Wall::getNodeType() const
{
	return NodeType::WallNodeType;
}