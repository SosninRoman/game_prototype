#include "World.h"


World::World(sf::RenderWindow& window):
	mWindow(window), mWorldBounds(0.f, 0.f, mWindow.getSize().x, mWindow.getSize().y), pi(3.14159)
{
	buildScene();
}


void World::buildScene()
{
	for(int i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = std::move(layer);
	}

	sf::View gameView = mWindow.getView();

	std::unique_ptr<Ball> gBall(new Ball(sf::CircleShape(10.f)));
	mBall = gBall.get();
	mBall->setOutlineColor(sf::Color::Black);
	mBall->setOutlineThickness(1);
	mBall->setFillColor(sf::Color::White);
	mBall->setOrigin(sf::Vector2f(mBall->getSize() / 2, mBall->getSize() / 2));
	mBall->setPosition(gameView.getCenter().x, gameView.getCenter().y);
	ball_direction = rand() / static_cast<float>(RAND_MAX) * pi;//?
	mSceneLayers[Ground]->attachChild(std::move(gBall));
}

void World::draw()
{
	for(int i = 0; i < LayerCount; ++i)
	{
		mWindow.draw(*mSceneLayers[i]);
	}
}

void World::update(sf::Time dt)
{
}