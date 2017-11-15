#include "SBTAbstractAnimatedNode.h"

SBTAbstractAnimatedNode::SBTAbstractAnimatedNode(TextureHolder& textures):
	mAnimator(textures)
{
}

SBTAbstractAnimatedNode::~SBTAbstractAnimatedNode()
{
}

void SBTAbstractAnimatedNode::createAnimation(const string& name,  int textureID, sf::Time duration, bool loop, bool rotate, float degree)
{
	mAnimator.createAnimation(name, textureID, duration, loop, rotate, degree);
}

SBTAnimation* SBTAbstractAnimatedNode::findAnimation(const string& name)
{
	return mAnimator.findAnimation(name);
}

void SBTAbstractAnimatedNode::addFrames(const string& name, sf::Vector2i startFrom, const sf::Vector2i& frameSize, size_t frames)
{
	SBTAnimation* animation = mAnimator.findAnimation(name);
	animation->AddFrames(startFrom, frameSize, frames);
}
	
void SBTAbstractAnimatedNode::addFrames(const string& name, vector<sf::IntRect> frames)
{
	SBTAnimation* animation = mAnimator.findAnimation(name);
	animation->AddFrames(frames);
}

void SBTAbstractAnimatedNode::switchAnimation(string& name)
{
	if (findAnimation(name)->mRotation)
		rotate(findAnimation(name)->mAngle);
	mAnimator.switchAnimation(name);
	if (findAnimation(name)->mRotation)
		rotate(-findAnimation(name)->mAngle);
	centerOrigin();
}

void SBTAbstractAnimatedNode::switchAnimation(char* name)
{
	if (mAnimator.getCurrentAnimation() != nullptr && mAnimator.getCurrentAnimation()->mRotation)
		rotate(mAnimator.getCurrentAnimation()->mAngle);
	mAnimator.switchAnimation(name);
	if (findAnimation(string(name))->mRotation)
		rotate(-findAnimation(string(name))->mAngle);
	centerOrigin();
}

void SBTAbstractAnimatedNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	mAnimator.drawCurrent(target, states);
}

void SBTAbstractAnimatedNode::updateCurrent(sf::Time dt)
{
	mAnimator.update(dt);
}

sf::FloatRect SBTAbstractAnimatedNode::getSpriteBounds() const
{
	return mAnimator.getSprite().getGlobalBounds();
}

void SBTAbstractAnimatedNode::centerOrigin()
{
	auto sz = getSize();
	setOrigin(sf::Vector2f(static_cast<float>(getSize().x) / 2, static_cast<float>(getSize().y) / 2));
}

sf::Vector2u SBTAbstractAnimatedNode::getSize()
{
	return mAnimator.getSize();
}

sf::FloatRect SBTAbstractAnimatedNode::getGlobalBounds() const
{
	return getTransform().transformRect( getSpriteBounds() );
}