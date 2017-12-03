#include "Wall.h"

Wall::Wall():
		SBTAbstractUnvisibleNode()
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