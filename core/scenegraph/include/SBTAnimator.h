#pragma once
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <SFML\Graphics.hpp>
#include "ResourceHolder.h"
#include "SBTTileSheet.h"
#include "SBTAnimation.h"

using std::string;
using std::vector;
using std::map;

class SBTAnimator
{
public:
	typedef map<string, SBTAnimation>::iterator map_iterator;

	explicit SBTAnimator(TextureHolder& textures);

	SBTAnimation* createAnimation(const string& name, int textureID, sf::Time duration, bool loop, bool rotate = false, float degree = 0);
	
	void switchAnimation(const string& name);
	
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	
	void update(sf::Time dt);

	const sf::Sprite& getSprite() const;
	
	sf::Vector2u getSize();

	SBTAnimation* findAnimation(const string& name);

	const SBTAnimation* getCurrentAnimation(){return (mCurrentAnimation == mAnimations.end())? nullptr : &(mCurrentAnimation->second);}
private:
	sf::Sprite					mSprite;
	
	sf::Time					mCurrentTime;
	
	map<string, SBTAnimation>		mAnimations;
	
	map_iterator				mCurrentAnimation;
	
	TextureHolder&              mTextures;
};



