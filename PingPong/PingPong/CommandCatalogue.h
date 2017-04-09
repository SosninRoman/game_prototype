#pragma once
#include <SFML\Graphics.hpp>

template <class MoveableNode>
class Mover
{
public:
	Mover(float vx, float vy):v(vx,vy){}
	void operator() (MoveableNode& node, sf::Time dt) const
	{
		node.accelerate(v);
	}
private:
	sf::Vector2f v;
};

template <class MoveableNode>
class PositionAdopter
{
public:
	PositionAdopter(const sf::View& view):mView(view){}
	void operator() (MoveableNode& node, sf::Time dt) const
	{
		sf::FloatRect viewBounds(mView.getCenter() - mView.getSize() / 2.f, mView.getSize());

		sf::Vector2f position = node.getPosition();
		if ( (position.y - node.getSize().y / 2) < viewBounds.top) position.y = viewBounds.top + node.getSize().y / 2;
		if ( (position.y + node.getSize().y / 2) > viewBounds.top + viewBounds.height) position.y = viewBounds.top + viewBounds.height - node.getSize().y / 2;
		node.setPosition(position);
	}
private:
	const sf::View& mView;
};

template <class MoveableNode>
class BallWallCollider
{
public:
	BallWallCollider(const sf::View& view):mView(view){}
	void operator() (MoveableNode& node, sf::Time dt) const
	{
		sf::FloatRect viewBounds(mView.getCenter() - mView.getSize() / 2.f, mView.getSize());

		if (node.getPosition().y - node.getSize() < viewBounds.top)
		{
			node.setVelocity(node.getVelocity().x, -node.getVelocity().y);
		}
		if (node.getPosition().y + node.getSize() > viewBounds.height)
		{
			node.setVelocity(node.getVelocity().x, -node.getVelocity().y);
		}
	}
private:
	const sf::View& mView;
};