#pragma once
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <SFML\Graphics.hpp>
#include "ResourceHolder.h"

using std::string;
using std::vector;
using std::map;

class Animator
{
public:
	struct Animation
	{
		TextureID				mTextureID;
		sf::Time				mDuration;
		bool					mLooping;
		vector<sf::IntRect>		mFrames;

		Animation(TextureID textureID, sf::Time& duration, bool looping):
			mTextureID(textureID), mDuration(duration), mLooping(looping){}
		void AddFrames(sf::Vector2i startFrom, const sf::Vector2i& frameSize, size_t frames);		
	};
	typedef map<string, Animation>::iterator map_iterator;

	Animator(TextureHolder& textures);

	Animation* createAnimation(const string& name, TextureID id, sf::Time duration, bool loop);
	void switchAnimation(const string& name);
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(sf::Time dt);
private:
	sf::Sprite					mSprite;
	sf::Time					mCurrentTime;
	map<string, Animation>		mAnimations;
	map_iterator				mCurrentAnimation;
	TextureHolder&              mTextures;
};



