#pragma once
#include "SBTCommandQueue.h"
#include "Paddle.h"
#include "CommandCatalogue.h"
#include "SBTAbstractCommandManager.h"

class Player: public SBTAbstractCommandManager
{
public:
	enum ActionType
	{
		LeftPaddleUp,
		LeftPaddleDown,
		RightPaddleUp,
		RightPaddleDown,
		StopLeftPaddle,
		StopRightPaddle
	};

	Player();
public:
	void handleEvent(const sf::Event& event, SBTCommandQueue& commands);

	bool isRealtimeAction(int type) const;

	void InitializeCommands();
};

