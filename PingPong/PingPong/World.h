#pragma once
#include <array>
#include <SFML\Graphics.hpp>
#include "SceneNode.h"
#include "Ball.h"
#include "Paddle.h"

class World: public sf::NonCopyable
{
public:
	enum Layer
	{
		BackGround,
		Ground,
		LayerCount
	};
	World(sf::RenderWindow& window);
	void draw();
	void update(sf::Time dt);
	//
	void handleEvent(const sf::Event& event);
	bool theEnd(){return the_end;}
private:
	std::array<SceneNode::Ptr, LayerCount> mSceneLayers;
	sf::RenderWindow& mWindow;
	sf::FloatRect mWorldBounds;

	void buildScene();

	bool the_end;
	sf::Vector2f paddle_size;
	Ball* mBall;
	Paddle* mRightPaddle, *mLeftPaddle;
};

