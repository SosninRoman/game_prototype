#include "Cube.h"

Cube::Cube(TextureHolder& textures):
	SceneNode(), AnimatedNode(textures), mAnimator(textures), mRemove(false)
{
	AnimatedNode::createAnimation("cub1",CubeTexture,sf::seconds(2),false);
	AnimatedNode::addFrames(string("cub1"), sf::Vector2i(0,0), sf::Vector2i(32,32),1);
	AnimatedNode::switchAnimation("cub1");
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
	return AnimatedNode::getGlobalBounds();
}

void Cube::centerOrigin()
{
	AnimatedNode::centerOrigin();
}

void Cube::updateCurrent(sf::Time dt)
{
	AnimatedNode::updateCurrent(dt);
}

void Cube::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	AnimatedNode::drawCurrent(target, states);
}

void Cube::kill()
{
	mRemove = true;
}

bool Cube::isMarkedForRemove()
{
	return mRemove;
}