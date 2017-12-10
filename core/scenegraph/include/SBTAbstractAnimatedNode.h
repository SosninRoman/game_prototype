#pragma once
#include "SBTAnimator.h"
#include "SBTAbstractSceneNode.h"

class SBTAbstractAnimatedNode: public virtual SBTAbstractSceneNode
{
public:
    typedef std::string animationID;
	//explicit SBTAbstractAnimatedNode(AtlasHolder& textures);
	explicit SBTAbstractAnimatedNode(GraphicResourceHolder& textures);
	~SBTAbstractAnimatedNode() override = default;

	void addAnimation(const std::string& SpriteAtlasID, const string& sequenceIDInAtlas,
					  const animationID& animationNameInAnimator, sf::Time duration, bool looping);

	void					switchAnimation(string& animationNameInAnimator);
	void					switchAnimation(char* animationNameInAnimator);

	sf::FloatRect	getGlobalBounds() const override;
	virtual sf::FloatRect	getSpriteBounds() const;
	void			centerOrigin() override;

	sf::Vector2u			getSize();
protected:
	void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	void			updateCurrent(sf::Time dt) override;
private:	
	SBTAnimation*	findAnimation(const string& name);
	SBTAnimator				m_animator;
};

