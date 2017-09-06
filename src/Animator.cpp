#include "Animator.h"

Animator::Animator(TextureHolder& textures):
	mTextures(textures), mCurrentAnimation(mAnimations.end())
{
}

Animator::Animation* Animator::createAnimation(const string& name, TextureID id, sf::Time duration, bool loop, bool rotate, float degree)
{
	Animation anim(id, duration, loop, rotate, degree);
	auto pair = mAnimations.insert(std::make_pair(name, anim));
	assert(pair.second);
	return &(pair.first)->second;
}

void Animator::switchAnimation(const string& name)
{
	mCurrentAnimation = mAnimations.find(name);
	assert(mCurrentAnimation != mAnimations.end());
	TileSheet& sheet = mTextures.get(mCurrentAnimation->second.mTextureID);
	const sf::Texture& texture = sheet.getTexture();
	mSprite.setTexture(texture);
	mCurrentTime = sf::Time::Zero;
	//
	mSprite.setTextureRect(mCurrentAnimation->second.mFrames[0]);
}

void Animator::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{	
	target.draw(mSprite, states);
}

void Animator::update(sf::Time dt)
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

const sf::Sprite& Animator::getSprite() const
{
	return mSprite;
}

sf::Vector2u Animator::getSize()
{
	return sf::Vector2u(mSprite.getTextureRect().width, mSprite.getTextureRect().height);
}

void Animator::Animation::AddFrames(sf::Vector2i startFrom, const sf::Vector2i& frameSize, size_t frames)
{
	for(size_t i = 0; i < frames; ++i)
	{
		mFrames.emplace_back(sf::IntRect(startFrom.x, startFrom.y, frameSize.x, frameSize.y));
		startFrom.x += frameSize.x;
	}
}

void Animator::Animation::AddFrames(vector<sf::IntRect> frames)
{
	mFrames.assign(frames.begin(), frames.end());
}

Animator::Animation* Animator::findAnimation(const string& name)
{
	auto itr = mAnimations.find(name);
	assert(itr != mAnimations.end());
	return &(itr->second);
}