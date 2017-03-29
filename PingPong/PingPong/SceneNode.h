#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <SFML\Graphics.hpp>

class SceneNode: public sf::Drawable, public sf::Transformable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;

	SceneNode():mParent(nullptr){}

	void attachChild(Ptr Child);
	Ptr detachChild(const SceneNode& Child);
	void update(sf::Time dt);

	sf::Transform getWorldTransform() const;
	sf::Vector2f getWorldPosition() const;
private:
	std::vector<Ptr> mChildren;
	SceneNode* mParent;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {}

	virtual void updateCurrent(sf::Time dt){}
};

