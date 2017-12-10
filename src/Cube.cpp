#include "Cube.h"

Cube::Cube(sf::Sprite& sprite):
	SBTAbstractSceneNode(), SBTAbstractSpriteNode(sprite),  m_remove(false)
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
	m_remove = true;
}

bool Cube::isMarkedForRemove()
{
	return m_remove;
}