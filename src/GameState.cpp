#include "GameState.h"
#include <random>

GameState::GameState(StateStack& stack, Context context, state_param_ptr param):
	State(stack, context, move(param) ),  mWorld(*context.window, *context.textures), mPlayer(*context.player)
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
		requestStackPush(ID::GameOver,state_param_ptr(new GameOverParam(mWorld.getWinner() ) ) );
		//requestStateCLear();
		//requestStackPush(ID::Title);
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
					if(event.key.code == sf::Keyboard::Escape)
						requestStackPush(ID::Pause);
					CommandQueue& queue = mWorld.getCommandQueue();
					mPlayer.handleEvent(event, queue);
				}
			case sf::Event::KeyReleased:
				{
					CommandQueue& queue = mWorld.getCommandQueue();
					mPlayer.handleEvent(event, queue);
				}
			}
	return true;
}

