#pragma once
#include <SFML\Graphics.hpp>
#include "SBTGameWindow.h"
#include "SBTAbstractSceneNode.h"
#include "RecieverTypeEnum.h"

template <class MoveableNode>
class PaddleMover
{
public:
	PaddleMover(float vx, float vy):v(vx,vy){}
	void operator() (SBTAbstractSceneNode& node, sf::Time dt) const
	{
		float speed = dynamic_cast<MoveableNode&>(node).getSpeed();
		
		node.SetLinearVelocity(b2Vec2(v.x * pixel_to_metr(speed),v.y * pixel_to_metr(speed)));
	}
private:
	sf::Vector2f v;
};

template <class MoveableNode>
class PositionAdopter
{
public:
	explicit PositionAdopter(const sf::View& view):mView(view){}
	void operator() (MoveableNode& node, sf::Time dt) const
	{
		sf::FloatRect viewBounds(mView.getCenter() - mView.getSize() / 2.f, mView.getSize());

		sf::Vector2f position = node.getPosition();

		if ( (position.y - node.getSize().y / 2) < viewBounds.top) 
			position.y = viewBounds.top + node.getSize().y / 2;
		
		if ( (position.y + node.getSize().y / 2) > viewBounds.top + viewBounds.height) 
			position.y = viewBounds.top + viewBounds.height - node.getSize().y / 2;
		
		node.setPosition(position);
	}
private:
	const sf::View& mView;
};

template<class Node, class World>
class CheckEndOfGame
{
public:
	explicit CheckEndOfGame(World* wor):
		world(wor){}
	void operator()(Node& node, sf::Time dt) const
	{
		SBTGameWindow& window = world->getWindow();

		if(node.getPosition().x - node.getSize().x / 2 < 0.f || node.getPosition().x + node.getSize().x / 2 > window.getResolution().x )
		{
			world->setEndGame();
			
			if(node.getPosition().x - node.getSize().x / 2 < 0.f)
				world->setWinner(RecieverType::RightPaddleRecieverType);
			else
				world->setWinner(RecieverType::LeftPaddleRecieverType);
		}
	}
private:
	World* world;
};