#include "Player.h"

Player::Player()
{
	mKeyBinding[sf::Keyboard::Up]   =    ActionType::RightPaddleUp;
	mKeyBinding[sf::Keyboard::Down] =    ActionType::RightPaddleDown;
	mKeyBinding[sf::Keyboard::W]    =    ActionType::LeftPaddleUp;
	mKeyBinding[sf::Keyboard::S]    =    ActionType::LeftPaddleDown;

	InitializeCommands();
}


void Player::InitializeCommands()
{
	mActions[ActionType::RightPaddleDown].action = derivedAction<Paddle>(PaddleMover<Paddle>(0,1));
	mActions[ActionType::RightPaddleDown].category = RecieverType::RightPaddle;

	mActions[ActionType::RightPaddleUp].action = derivedAction<Paddle>(PaddleMover<Paddle>(0,-1));
	mActions[ActionType::RightPaddleUp].category = RecieverType::RightPaddle;

	mActions[ActionType::LeftPaddleDown].action = derivedAction<Paddle>(PaddleMover<Paddle>(0,1));
	mActions[ActionType::LeftPaddleDown].category = RecieverType::LeftPaddle;

	mActions[ActionType::LeftPaddleUp].action = derivedAction<Paddle>(PaddleMover<Paddle>(0,-1));
	mActions[ActionType::LeftPaddleUp].category = RecieverType::LeftPaddle;

	mActions[ActionType::StopLeftPaddle].action = derivedAction<Paddle>(PaddleMover<Paddle>(0,0));
	mActions[ActionType::StopLeftPaddle].category = RecieverType::LeftPaddle;

	mActions[ActionType::StopRightPaddle].action = derivedAction<Paddle>(PaddleMover<Paddle>(0,0));
	mActions[ActionType::StopRightPaddle].category = RecieverType::RightPaddle;
}


bool Player::isRealtimeAction(ActionType type) const
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

void Player::handleRealtimeInput(CommandQueue& commands)
{
	std::for_each(mKeyBinding.begin(), mKeyBinding.end(), 
		[&commands, this](const std::pair<sf::Keyboard::Key,ActionType>& pair)
		{
			if(sf::Keyboard::isKeyPressed(pair.first) && this->isRealtimeAction(pair.second))
				commands.Push(mActions[pair.second]);
		}
	);
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyReleased )
	{
		if(event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)
			commands.Push(mActions[ActionType::StopRightPaddle]);
		if(event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S)
			commands.Push(mActions[ActionType::StopLeftPaddle]);
	}
}