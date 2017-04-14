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
	mActions[ActionType::RightPaddleDown].action = derivedAction<Paddle>(Mover<Paddle>(0,1));
	mActions[ActionType::RightPaddleDown].category = RecieverType::RightPaddle;

	mActions[ActionType::RightPaddleUp].action = derivedAction<Paddle>(Mover<Paddle>(0,-1));
	mActions[ActionType::RightPaddleUp].category = RecieverType::RightPaddle;

	mActions[ActionType::LeftPaddleDown].action = derivedAction<Paddle>(Mover<Paddle>(0,1));
	mActions[ActionType::LeftPaddleDown].category = RecieverType::LeftPaddle;

	mActions[ActionType::LeftPaddleUp].action = derivedAction<Paddle>(Mover<Paddle>(0,-1));
	mActions[ActionType::LeftPaddleUp].category = RecieverType::LeftPaddle;
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

}