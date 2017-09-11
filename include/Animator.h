#pragma once
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <SFML\Graphics.hpp>
#include "ResourceHolder.h"
#include "TileSheet.h"

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

		bool                    mRotation;
		
		float                   mAngle;

		Animation(TextureID textureID, sf::Time& duration, bool looping, bool rotate = false, float degree = 0):
			mTextureID(textureID), 
			mDuration(duration), 
			mLooping(looping), 
			mRotation(rotate), 
			mAngle(degree)
		{
		}
		
		void AddFrames(sf::Vector2i startFrom, const sf::Vector2i& frameSize, size_t frames);
		
		void AddFrames(vector<sf::IntRect> frames);
	};

	typedef map<string, Animation>::iterator map_iterator;

	Animator(TextureHolder& textures);

	Animation* createAnimation(const string& name, TextureID id, sf::Time duration, bool loop, bool rotate = false, float degree = 0);
	
	void switchAnimation(const string& name);
	
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	
	void update(sf::Time dt);

	const sf::Sprite& getSprite() const;
	
	sf::Vector2u getSize();

	Animation* findAnimation(const string& name);

	const Animation* getCurrentAnimation(){return (mCurrentAnimation == mAnimations.end())? nullptr : &(mCurrentAnimation->second);}
private:
	sf::Sprite					mSprite;
	
	sf::Time					mCurrentTime;
	
	map<string, Animation>		mAnimations;
	
	map_iterator				mCurrentAnimation;
	
	TextureHolder&              mTextures;
};



