#include "SBTAbstractAnimatedNode.h"
#include "SBTAnimation.h"
#include "SBTSpriteSequence.h"
#include "SBTSequenceState.h"

SBTAbstractAnimatedNode::SBTAbstractAnimatedNode(AtlasHolder& textures):
	m_animator(textures)
{
}

void SBTAbstractAnimatedNode::addAnimation(const std::string& SpriteAtlasID, const string& sequenceIDInAtlas,
				  const animationID& animationNameInAnimator, sf::Time duration, bool looping)
{
	m_animator.addAnimation(SpriteAtlasID, sequenceIDInAtlas, animationNameInAnimator, duration, looping);
}

SBTAnimation* SBTAbstractAnimatedNode::findAnimation(const string& name)
{
	return m_animator.findAnimation(name);
}

void SBTAbstractAnimatedNode::switchAnimation(string& name)
{
	m_animator.switchAnimation(name);
	centerOrigin();
}

void SBTAbstractAnimatedNode::switchAnimation(char* name)
{
	m_animator.switchAnimation(name);
	centerOrigin();
}

void SBTAbstractAnimatedNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	m_animator.drawCurrent(target, states);
}

void SBTAbstractAnimatedNode::updateCurrent(sf::Time dt)
{
	m_animator.update(dt);
}

sf::FloatRect SBTAbstractAnimatedNode::getSpriteBounds() const
{
	return m_animator.getRenderSprite().getGlobalBounds();
}

void SBTAbstractAnimatedNode::centerOrigin()
{
	auto sz = getSize();
	setOrigin(sf::Vector2f(static_cast<float>(getSize().x) / 2, static_cast<float>(getSize().y) / 2));
}

sf::Vector2u SBTAbstractAnimatedNode::getSize()
{
	return m_animator.getSize();
}

sf::FloatRect SBTAbstractAnimatedNode::getGlobalBounds() const
{
	return getTransform().transformRect( getSpriteBounds() );
}