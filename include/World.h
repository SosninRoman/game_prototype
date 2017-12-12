#pragma once
#include "Ball.h"
#include "Paddle.h"
#include "Cube.h"
#include "Wall.h"
#include "SBTAbstractWorld.h"
#include "MyContactListener.h"

class World: public SBTAbstractWorld
{

public:
	enum Layer
	{
		BackGround,
		Ground,
		LayerCount
	};

	World(SBTGameWindow& window, GraphicResourceHolder* graphicRes);

	bool									theEnd(){return the_end;}
	
	void									setEndGame();
	
	void									setWinner(RecieverType type){mWinner = type;}
	
	RecieverType							getWinner(){return mWinner;}

    int                                     layerCount() override {return LayerCount;}

    void                                    produceAndPushCommands() override;

    void                                    postfix() override;
private:
	void									buildScene() override;

	bool									the_end = false;
	
	RecieverType							mWinner;
};

