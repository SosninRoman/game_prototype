#include "GameState.h"
#include <random>



GameState::GameState(StateStack& stack, Context context):
	State(stack, context),  mWorld(*context.window), mPlayer(*context.player)
{
}

void GameState::draw()
{
	mWorld.draw();
}

bool GameState::update(sf::Time dt)
{
	mWorld.update(dt);
	CommandQueue& queue = mWorld.getCommandQueue();
	mPlayer.handleRealtimeInput(queue);
	if (mWorld.theEnd())
	{
		requestStateCLear();
		requestStackPush(ID::Title);
	}
	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	sf::View gameView = getContext().window->getView();
	sf::Vector2u gameWindowSize = getContext().window->getSize();
	switch(event.type)
			{

			case sf::Event::EventType::Closed:         
				requestStateCLear();
					break;
			case sf::Event::EventType::KeyPressed:
				{
					CommandQueue& queue = mWorld.getCommandQueue();
					mPlayer.handleEvent(event, queue);
				//mWorld.handleEvent(event);
				}
			}
	return true;
}