#pragma once
#include <array>
#include <SFML\Graphics.hpp>
#include "SceneNode.h"
#include "Ball.h"
#include "Paddle.h"
#include "Cube.h"
#include "SpriteNode.h"
#include "CommandQueue.h"
#include "CommandCatalogue.h"
#include "ResourceHolder.h"

class World: public sf::NonCopyable
{
public:
	enum Layer
	{
		BackGround,
		Ground,
		LayerCount
	};
	World(sf::RenderWindow& window, TextureHolder& textures);
	void draw();
	void update(sf::Time dt);
	//
	void handleEvent(const sf::Event& event);
	bool theEnd(){return the_end;}

	CommandQueue& getCommandQueue() ;
	void handleCollisions();
private:
	std::array<SceneNode::Ptr, LayerCount> mSceneLayers;
	sf::RenderWindow& mWindow;
	sf::FloatRect mWorldBounds;

	void buildScene();

	bool the_end;
	Ball* mBall;

	CommandQueue mCommandQueue;

	TextureHolder& mTextures;
};

