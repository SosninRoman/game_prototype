#pragma once
#include <vector>
#include <memory>
#include <set>
#include <algorithm>
#include <SFML\Graphics.hpp>
#include "Command.h"

enum class NodeType
{
	None = 0,
	Scene = 1,
	Paddle = 1 << 1,
	Ball = 1 << 2,
};

class SceneNode: public sf::Drawable, public sf::Transformable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;
	typedef std::pair<SceneNode*, SceneNode*> Pair;

	SceneNode():mParent(nullptr){}
	virtual ~SceneNode(){}

	void attachChild(Ptr Child);
	Ptr detachChild(const SceneNode& Child);
	void update(sf::Time dt);

	sf::Transform getWorldTransform() const;
	sf::Vector2f getWorldPosition() const;

	virtual RecieverType getActionType() const;
	virtual NodeType getNodeType() const;
	void onCommand(const Command& command, sf::Time dt);

	virtual sf::FloatRect getGlobalBounds() const;

	void checkNodeCollision(SceneNode& node, std::set<Pair>& collisions);
	void checkSceneCollision(SceneNode& node, std::set<Pair>& collisions);
private:
	std::vector<Ptr> mChildren;
	SceneNode* mParent;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {}

	virtual void updateCurrent(sf::Time dt){}
};

