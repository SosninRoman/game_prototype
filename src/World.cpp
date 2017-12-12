#include "World.h"
#include <iostream>
#include "CommandCatalogue.h"
#include "ResourcesIDEnum.h"

float pi = 3.14159f;

World::World(SBTGameWindow& window, GraphicResourceHolder* graphicRes):
    SBTAbstractWorld(static_cast<int>(LayerCount), window, graphicRes, sf::FloatRect(0.f, 0.f, static_cast<float>(window.getResolution().x), static_cast<float>(window.getResolution().y)),
    new myContactListener(this), b2Vec2(0,00), new SBTCommandQueue() )
{
	buildScene();
}

void World::buildScene()
{
    loadLevel("../res/pong_map.tmx");
	//
	for(size_t i = 0; i < layerCount(); ++i)
	{
        SBTAbstractSceneNode::Ptr layer(new LayerNode() );
        getSceneLayer(i) = std::move(layer);
	}
    sf::View gameView = getWindow().getView();

	//BALL CREATING
	sf::Vector2f ball_center(gameView.getCenter().x, gameView.getCenter().y);

	std::unique_ptr<Ball> gBall( new Ball(getGraphicResourses(), ball_center) );

	gBall->addAnimation("BallTexture", "ball_animation", "ball_animation", sf::seconds(2), true);

	gBall->switchAnimation("ball_animation");

	b2Body* Body = createCircleBody(gBall->getPosition().x, gBall->getPosition().y, gBall->getSize().x/2, b2_dynamicBody, 1.f);

	Body->SetLinearVelocity(b2Vec2(-5, 0.f));

	gBall->setBody(Body);

    getSceneLayer(Ground)->attachChild(std::move(gBall));

	//LEFT PADDLE CREATING
    std::unique_ptr<Paddle> gLPaddle(new Paddle(RecieverType::LeftPaddleRecieverType, getGraphicResourses() ) );

    gLPaddle->addAnimation("PaddleTexture", "paddle_animation", "paddle_up", sf::seconds(2), false);

	gLPaddle->switchAnimation("paddle_up");

    gLPaddle->addAnimation("PaddleTexture", "paddle_animation", "paddle_down", sf::seconds(2), false);

	gLPaddle->switchAnimation("paddle_down");

	gLPaddle->centerOrigin();

	sf::Vector2u tmp_sz = (*gLPaddle).getSize();

    sf::Vector2f l_pos(static_cast<float>(tmp_sz.x) / 2, static_cast<float>(getWindow().getResolution().y / 2));

	gLPaddle->setPosition(l_pos);

	auto gLbounds = gLPaddle->getGlobalBounds();

	gLPaddle->setBody(createBoxBody(l_pos.x, l_pos.y, gLbounds.width, gLbounds.height, b2_dynamicBody, 10000, true) );

	getSceneLayer(Ground)->attachChild(std::move(gLPaddle));

	//RIGHT PADDLE CREATING
    std::unique_ptr<Paddle> gRPaddle(new Paddle(RecieverType::RightPaddleRecieverType, getGraphicResourses() ) );

    sf::Vector2f r_pos(static_cast<float>(getWindow().getResolution().x - tmp_sz.x / 2), static_cast<float>(getWindow().getResolution().y / 2));

	gRPaddle->setPosition(r_pos);

    gRPaddle->addAnimation("PaddleTexture", "paddle_animation", "paddle_up", sf::seconds(2), false);

	gRPaddle->switchAnimation("paddle_up");

    gRPaddle->addAnimation("PaddleTexture", "paddle_animation", "paddle_down", sf::seconds(2), false);

	gRPaddle->switchAnimation("paddle_down");

	auto gRbounds = gRPaddle->getGlobalBounds();

	gRPaddle->setBody(createBoxBody(r_pos.x, r_pos.y, gRbounds.width, gRbounds.height, b2_dynamicBody, 10000, true) );

	getSceneLayer(Ground)->attachChild(std::move(gRPaddle));

	//FILLING SCENE BY OBJECTS FROM THE MAP
    vector<LevelObject>& objects = getLevel().getAllObjects();

	for( auto& obj : objects)
	{
		if(obj.type == "Cube")
		{
			std::unique_ptr<Cube> map_Cube(new Cube(obj.sprite));

			sf::Rect<int> rect = obj.rect;

			map_Cube->centerOrigin();

			map_Cube->setPosition(static_cast<float>(rect.left) + static_cast<float>(rect.width) / 2 ,
				static_cast<float>(rect.top) - static_cast<float>(rect.height) / 2);

			map_Cube->setBody(createBoxBody(map_Cube->getPosition().x, map_Cube->getPosition().y,
				obj.sprite.getTextureRect().height, obj.sprite.getTextureRect().width, b2_staticBody));

			getSceneLayer(Ground)->attachChild(std::move(map_Cube));
		}
		if(obj.type == "Wall")
		{
			std::unique_ptr<Wall> map_Wall(new Wall());

			map_Wall->setRectangle(obj.rect);

			map_Wall->setPosition(obj.rect.left, obj.rect.top);

			map_Wall->setBody(createBoxBody(obj.rect.left + obj.rect.width / 2, obj.rect.top + obj.rect.height / 2,  obj.rect.width, obj.rect.height, b2_staticBody) );

			getSceneLayer(Ground)->attachChild(std::move(map_Wall));
		}
	}
}

void World::postfix()
{
    getSceneLayer(Ground)->removeWrecks();
}

void World::setEndGame()
{
	the_end = true;
}

void World::produceAndPushCommands()
{
    SBTCommand LeftPaddleAdopter;

    LeftPaddleAdopter.action = derivedAction<Paddle>( PositionAdopter<Paddle>(getWindow().getView() ) );

    LeftPaddleAdopter.category = RecieverType::LeftPaddleRecieverType;

    getCommandQueue().Push(LeftPaddleAdopter);

    SBTCommand RightPaddleAdopter;

    RightPaddleAdopter.action = derivedAction<Paddle>( PositionAdopter<Paddle>(getWindow().getView() ) );

    RightPaddleAdopter.category = RecieverType::RightPaddleRecieverType;

    getCommandQueue().Push(RightPaddleAdopter);

    SBTCommand CheckEnd;

    CheckEnd.action = derivedAction<Ball>( CheckEndOfGame<Ball, World>(this) );

    CheckEnd.category = RecieverType::BallRecieverType;

    getCommandQueue().Push(CheckEnd);
}