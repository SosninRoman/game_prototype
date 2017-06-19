#pragma once
#include <map>
#include "CommandQueue.h"
#include <SFML\Graphics.hpp>
#include "Paddle.h"
#include "CommandCatalogue.h"

class Player
{
public:
	enum class ActionType
	{
		LeftPaddleUp,
		LeftPaddleDown,
		RightPaddleUp,
		RightPaddleDown,
	};

	Player();
public:
	void handleEvent(const sf::Event& event, CommandQueue& commands);
	void handleRealtimeInput(CommandQueue& commands);

	bool isRealtimeAction(ActionType type) const;
	void InitializeCommands();
private:
	std::map<ActionType,Command>           mActions;
	std::map<sf::Keyboard::Key,ActionType> mKeyBinding;
};

