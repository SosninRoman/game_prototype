#include "Cube.h"

Cube::Cube(sf::Sprite& textures):
	SceneNode(), SpriteNode(textures),  mRemove(false)
{
	
}

RecieverType Cube::getActionType() const
{
	return RecieverType::Cube;
}

NodeType Cube::getNodeType() const
{
	return NodeType::Cube;
}

sf::FloatRect Cube::getGlobalBounds() const
{
	return SpriteNode::getGlobalBounds();
}

void Cube::centerOrigin()
{
	SpriteNode::centerOrigin();
}

void Cube::updateCurrent(sf::Time dt)
{
	//SpriteNode::updateCurrent(dt);
	SceneNode::updateCurrent(dt);
}

void Cube::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	SpriteNode::drawCurrent(target, states);
}

void Cube::kill()
{
	mRemove = true;
}

bool Cube::isMarkedForRemove()
{
	return mRemove;
}