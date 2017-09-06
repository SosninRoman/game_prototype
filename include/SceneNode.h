#pragma once
#include <vector>
#include <memory>
#include <set>
#include <algorithm>
#include <SFML\Graphics.hpp>
#include "Command.h"
#include <Box2D\Box2D.h>

enum class NodeType
{
	None = 0,
	Scene = 1,
	Paddle = 1 << 1,
	Ball = 1 << 2,
	Cube = 1 << 3,
	Wall = 1 << 4,
};

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

class SceneNode: public sf::Drawable, public sf::Transformable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;
	typedef std::pair<SceneNode*, SceneNode*> Pair;

	SceneNode();

	virtual ~SceneNode();

	void					attachChild(Ptr Child);
	Ptr						detachChild(const SceneNode& Child);
	void					update(sf::Time dt);

	sf::Transform			getWorldTransform() const;
	sf::Vector2f			getWorldPosition() const;

	virtual RecieverType	getActionType() const;
	virtual NodeType		getNodeType() const;
	void					onCommand(const Command& command, sf::Time dt);

	virtual sf::FloatRect	getGlobalBounds() const;

	void					checkNodeCollision(SceneNode& node, std::set<Pair>& collisions);
	void					checkSceneCollision(SceneNode& node, std::set<Pair>& collisions);

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
	SceneNode*				mParent;	

	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {}	
	void removeBody();
	
};

