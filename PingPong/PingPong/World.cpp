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