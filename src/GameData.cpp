#include "GameData.h"
#include "Paddle.h"

std::vector<PaddleData>	initializePaddleData()
{
	std::vector<PaddleData> data(static_cast<int>(Paddle::PaddleType::NumOfTypes));

	data[static_cast<int>(Paddle::PaddleType::LeftPaddle)].speed = 200.f;
	
	data[static_cast<int>(Paddle::PaddleType::RightPaddle)].speed = 200.f;
	
	return data;
}