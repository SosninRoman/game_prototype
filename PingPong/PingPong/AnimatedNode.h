#pragma once
#include "Animator.h"
#include "ResourceHolder.h"
#include "SceneNode.h"

class AnimatedNode: public virtual SceneNode
{
public:
	AnimatedNode(TextureHolder& textures);
	~AnimatedNode();
	
	void					createAnimation(const string& name, TextureID id, sf::Time duration, bool loop, bool rotate = false, float degree = 0);
	void					addFrames(string& name, sf::Vector2i startFrom, const sf::Vector2i& frameSize, size_t frames);
	void					addFrames(string& name, vector<sf::IntRect> frames);

	void					switchAnimation(string& name);
	void					switchAnimation(char* name);

	virtual sf::FloatRect	getGlobalBounds() const;
	virtual sf::FloatRect	getSpriteBounds() const;
	virtual void			centerOrigin();

	sf::Vector2u			getSize();
protected:
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void			updateCurrent(sf::Time dt);
private:	
	Animator::Animation*	findAnimation(string& name);
	Animator				mAnimator;
};

