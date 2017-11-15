#include "SBTAnimator.h"

SBTAnimator::SBTAnimator(TextureHolder& textures):
	mTextures(textures), mCurrentAnimation(mAnimations.end())
{
}

SBTAnimation* SBTAnimator::createAnimation(const string& name, int textureID, sf::Time duration, bool loop, bool rotate, float degree)
{
	SBTAnimation anim(textureID, duration, loop, rotate, degree);
	auto pair = mAnimations.insert(std::make_pair(name, anim));
	assert(pair.second);
	return &(pair.first)->second;
}

void SBTAnimator::switchAnimation(const string& name)
{
	mCurrentAnimation = mAnimations.find(name);
	assert(mCurrentAnimation != mAnimations.end());
	SBTTileSheet& sheet = mTextures.get(mCurrentAnimation->second.mTextureID);
	const sf::Texture& texture = sheet.getTexture();
	mSprite.setTexture(texture);
	mCurrentTime = sf::Time::Zero;
	//
	mSprite.setTextureRect(mCurrentAnimation->second.mFrames[0]);
}

void SBTAnimator::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{	
	target.draw(mSprite, states);
}

void SBTAnimator::update(sf::Time dt)
{
	if(!mAnimations.empty())
	{
		mCurrentTime += dt;
		auto animation = mCurrentAnimation->second;
		int frame = static_cast<int>(mCurrentTime.asSeconds() / animation.mDuration.asSeconds() * animation.mFrames.size());
		if(animation.mLooping)
			frame %= animation.mFrames.size();
		else
			frame = animation.mFrames.size() - 1;
		mSprite.setTextureRect(animation.mFrames[frame]);
	}
}

const sf::Sprite& SBTAnimator::getSprite() const
{
	return mSprite;
}

sf::Vector2u SBTAnimator::getSize()
{
	return sf::Vector2u(mSprite.getTextureRect().width, mSprite.getTextureRect().height);
}

SBTAnimation* SBTAnimator::findAnimation(const string& name)
{
	auto itr = mAnimations.find(name);
	assert(itr != mAnimations.end());
	return &(itr->second);
}