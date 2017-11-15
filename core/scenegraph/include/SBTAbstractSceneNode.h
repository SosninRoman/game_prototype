#pragma once
#include <vector>
#include <memory>
#include <set>
#include <algorithm>
#include <SFML\Graphics.hpp>
#include "SBTCommand.h"
#include <Box2D\Box2D.h>

template<class T>
T metr_to_pixel(T val)
{
	return val * 30;
}

template<class T>
T pixel_to_metr(T val)
{
	return val / 30;
}

class SBTAbstractSceneNode: public sf::Drawable, public sf::Transformable
{
public:
	typedef std::unique_ptr<SBTAbstractSceneNode> Ptr;
	typedef std::pair<SBTAbstractSceneNode*, SBTAbstractSceneNode*> Pair;

	SBTAbstractSceneNode();

	~SBTAbstractSceneNode() override;

	void					attachChild(Ptr Child);

    Ptr						detachChild(const SBTAbstractSceneNode& Child);

    void					update(sf::Time dt);

	sf::Transform			getWorldTransform() const;

    sf::Vector2f			getWorldPosition() const;

	virtual int             getActionType() const = 0;

    virtual int     		getNodeType() const = 0;

    void					onCommand(const SBTCommand& command, sf::Time dt);

	virtual sf::FloatRect	getGlobalBounds() const;

	void					checkNodeCollision(SBTAbstractSceneNode& node, std::set<Pair>& collisions);
	void					checkSceneCollision(SBTAbstractSceneNode& node, std::set<Pair>& collisions);

	virtual void			centerOrigin(){}

	virtual bool			isMarkedForRemove();

	void					removeWrecks();

	void					setBody(b2Body* b_ptr);

    void					SetLinearVelocity(b2Vec2 vel);

    b2Body* getBody(){return mBody;}
protected:
	virtual void			updateCurrent(sf::Time dt);
	b2Body*					mBody;
private:
	std::vector<Ptr>		mChildren;

	SBTAbstractSceneNode*				mParent;

	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {}	
	void removeBody();
	
};

