#include "Player.h"

Player::Player()
{
	setActionToKeyboard(sf::Keyboard::Up, ActionType::RightPaddleUp);
	setActionToKeyboard(sf::Keyboard::Down, ActionType::RightPaddleDown);
	setActionToKeyboard(sf::Keyboard::W, ActionType::LeftPaddleUp);
	setActionToKeyboard(sf::Keyboard::S, ActionType::LeftPaddleDown);

	InitializeCommands();
}


void Player::InitializeCommands()
{
	setCommand(ActionType::RightPaddleDown, derivedAction<Paddle>(PaddleMover<Paddle>(0,1)), RecieverType::RightPaddleRecieverType);
	setCommand(ActionType::RightPaddleUp, derivedAction<Paddle>(PaddleMover<Paddle>(0,-1)), RecieverType::RightPaddleRecieverType);
	setCommand(ActionType::LeftPaddleDown, derivedAction<Paddle>(PaddleMover<Paddle>(0,1)), RecieverType::LeftPaddleRecieverType);
	setCommand(ActionType::LeftPaddleUp, derivedAction<Paddle>(PaddleMover<Paddle>(0,-1)), RecieverType::LeftPaddleRecieverType);
	setCommand(ActionType::StopLeftPaddle, derivedAction<Paddle>(PaddleMover<Paddle>(0,0)), RecieverType::LeftPaddleRecieverType);
	setCommand(ActionType::StopRightPaddle, derivedAction<Paddle>(PaddleMover<Paddle>(0,0)), RecieverType::RightPaddleRecieverType);
}


bool Player::isRealtimeAction(int type) const
{
	switch(type)
	{
	case ActionType::LeftPaddleDown:
	case ActionType::LeftPaddleUp:
	case ActionType::RightPaddleDown:
	case ActionType::RightPaddleUp:
			return true;
	default:
			return false;
	}
}

void Player::handleEvent(const sf::Event& event, SBTCommandQueue& commands)
{
	if (event.type == sf::Event::KeyReleased )
	{
		if(event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)
			commands.Push(getCommand(ActionType::StopRightPaddle) );
		if(event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S)
			commands.Push(getCommand(ActionType::StopLeftPaddle) );
	}
}