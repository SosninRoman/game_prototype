#include "Wall.h"


Wall::Wall():
	SpriteNode(sf::Sprite())
{
}


Wall::~Wall()
{
}

RecieverType Wall::getActionType() const
{
	return RecieverType::Wall;
}

NodeType Wall::getNodeType() const
{
	return NodeType::Wall;
}