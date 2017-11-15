#pragma once
#include "SBTAnimator.h"
#include "ResourceHolder.h"
#include "SBTAbstractSceneNode.h"

class SBTAbstractAnimatedNode: public virtual SBTAbstractSceneNode
{
public:
	explicit SBTAbstractAnimatedNode(TextureHolder& textures);
	~SBTAbstractAnimatedNode();
	
	void					createAnimation(const string& name, int textureID, sf::Time duration, bool loop, bool rotate = false, float degree = 0);
	void					addFrames(const string& name, sf::Vector2i startFrom, const sf::Vector2i& frameSize, size_t frames);
	void					addFrames(const string& name, vector<sf::IntRect> frames);

	void					switchAnimation(string& name);
	void					switchAnimation(char* name);

	sf::FloatRect	getGlobalBounds() const override;
	virtual sf::FloatRect	getSpriteBounds() const;
	void			centerOrigin() override;

	sf::Vector2u			getSize();
protected:
	void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	void			updateCurrent(sf::Time dt) override;
private:	
	SBTAnimation*	findAnimation(const string& name);
	SBTAnimator				mAnimator;
};

