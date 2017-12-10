#include "GameState.h"
#include <random>
#include "StateIDEnum.h"
#include "GameOverStateParam.h"

GameState::GameState(SBTStateStack& stack, SBTContext context, state_param_ptr param):
		SBTAbstractApplicationState(stack, context, move(param) ),
		mWorld(*context.window, *context.graphicResources),
	mPlayer(dynamic_cast<Player*>(context.player) )
{

}

void GameState::draw()
{
	mWorld.draw();
}

bool GameState::update(sf::Time dt)
{
	mWorld.update(dt);
	
	SBTCommandQueue& queue = mWorld.getCommandQueue();
	
	mPlayer->handleRealtimeInput(queue);
	
	if (mWorld.theEnd())
	{
		requestStackPush(StateID::GameOver,state_param_ptr(new GameOverParam(mWorld.getWinner() ) ) );
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
						requestStackPush(StateID::Pause);
					SBTCommandQueue& queue = mWorld.getCommandQueue();
					mPlayer->handleEvent(event, queue);
				}
			case sf::Event::KeyReleased:
				{
					SBTCommandQueue& queue = mWorld.getCommandQueue();
					mPlayer->handleEvent(event, queue);
				}
			}
	return true;
}

