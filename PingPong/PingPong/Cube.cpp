#include "Cube.h"

Cube::Cube(TextureHolder& textures):
	mAnimator(textures), mRemove(false)
{
	auto animation = mAnimator.createAnimation("cub1",CubeTexture,sf::seconds(2),false);
	animation->AddFrames(sf::Vector2i(0,0), sf::Vector2i(32,32),1);
	mAnimator.switchAnimation("cub1");
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
	return getWorldTransform().transformRect(mAnimator.getSprite().getGlobalBounds());
}

void Cube::centerOrigin()
{
	mAnimator.centerOrigin();
}

void Cube::updateCurrent(sf::Time dt)
{
	mAnimator.update(dt);
}

void Cube::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	mAnimator.drawCurrent(target, states);
}

void Cube::kill()
{
	mRemove = true;
}

bool Cube::isMarkedForRemove()
{
	return mRemove;
}