#pragma once
#include <array>
#include <SFML\Graphics.hpp>
#include "SceneNode.h"
#include "Ball.h"
#include "Paddle.h"
#include "CommandQueue.h"

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

	CommandQueue& getCommandQueue() ;
private:
	std::array<SceneNode::Ptr, LayerCount> mSceneLayers;
	sf::RenderWindow& mWindow;
	sf::FloatRect mWorldBounds;

	void buildScene();

	bool the_end;
	Ball* mBall;
	Paddle* mRightPaddle, *mLeftPaddle;

	CommandQueue mCommandQueue;
};

