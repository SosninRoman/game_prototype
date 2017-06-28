#include "AnimatedNode.h"

AnimatedNode::AnimatedNode(TextureHolder& textures):
	mAnimator(textures)
{
}

AnimatedNode::~AnimatedNode(void)
{
}

void AnimatedNode::createAnimation(const string& name, TextureID id, sf::Time duration, bool loop, bool rotate, float degree)
{
	mAnimator.createAnimation(name, id, duration, loop, rotate, degree);
}

Animator::Animation* AnimatedNode::findAnimation(string& name)
{
	return mAnimator.findAnimation(name);
}

void AnimatedNode::addFrames(string& name, sf::Vector2i startFrom, const sf::Vector2i& frameSize, size_t frames)
{
	Animator::Animation* animation = mAnimator.findAnimation(name);
	animation->AddFrames(startFrom, frameSize, frames);
}
	
void AnimatedNode::addFrames(string& name, vector<sf::IntRect> frames)
{
	Animator::Animation* animation = mAnimator.findAnimation(name);
	animation->AddFrames(frames);
}

void AnimatedNode::switchAnimation(string& name)
{
	if (findAnimation(name)->mRotation)
		rotate(findAnimation(name)->mAngle);
	mAnimator.switchAnimation(name);
	if (findAnimation(name)->mRotation)
		rotate(-findAnimation(name)->mAngle);
	centerOrigin();
}

void AnimatedNode::switchAnimation(char* name)
{
	if (mAnimator.getCurrentAnimation() != nullptr && mAnimator.getCurrentAnimation()->mRotation)
		rotate(mAnimator.getCurrentAnimation()->mAngle);
	mAnimator.switchAnimation(name);
	if (findAnimation(string(name))->mRotation)
		rotate(-findAnimation(string(name))->mAngle);
	centerOrigin();
}

void AnimatedNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	mAnimator.drawCurrent(target, states);
}

void AnimatedNode::updateCurrent(sf::Time dt)
{
	mAnimator.update(dt);
}

sf::FloatRect AnimatedNode::getSpriteBounds() const
{
	return mAnimator.getSprite().getGlobalBounds();
}

void AnimatedNode::centerOrigin()
{
	auto sz = getSize();
	setOrigin(sf::Vector2f(static_cast<float>(getSize().x) / 2, static_cast<float>(getSize().y) / 2));
}

sf::Vector2u AnimatedNode::getSize()
{
	return mAnimator.getSize();
}

sf::FloatRect AnimatedNode::getGlobalBounds() const
{
	return getTransform().transformRect( getSpriteBounds() );
}