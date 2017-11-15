#include "Cube.h"
#include "RecieverTypeEnum.h"

Cube::Cube(sf::Sprite& textures):
	SBTAbstractSceneNode(), SBTAbstractSpriteNode(textures),  mRemove(false)
{
	
}

int Cube::getActionType() const
{
	return RecieverType::CubeRecieverType;
}

int Cube::getNodeType() const
{
	return NodeType::CubeNodeType;
}

sf::FloatRect Cube::getGlobalBounds() const
{
	return SBTAbstractSpriteNode::getGlobalBounds();
}

void Cube::centerOrigin()
{
	SBTAbstractSpriteNode::centerOrigin();
}

void Cube::updateCurrent(sf::Time dt)
{
	SBTAbstractSceneNode::updateCurrent(dt);
}

void Cube::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	SBTAbstractSpriteNode::drawCurrent(target, states);
}

void Cube::kill()
{
	mRemove = true;
}

bool Cube::isMarkedForRemove()
{
	return mRemove;
}