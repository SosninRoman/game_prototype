#include "World.h"
#include <iostream>

float pi = 3.14159f;
bool matchesCategories(SceneNode::Pair& colliders, NodeType type1, NodeType type2);

World::World(sf::RenderWindow& window, TextureHolder& textures):
	mWindow(window), mWorldBounds(0.f, 0.f, static_cast<float>(mWindow.getSize().x), static_cast<float>(mWindow.getSize().y)), the_end(false), mCommandQueue(), mTextures(textures)
{
	buildScene();
}

void World::buildScene()
{
	for(int i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = std::move(layer);
	}
	sf::View gameView = mWindow.getView();	
	//BALL CREATING
	std::unique_ptr<Ball> gBall(new Ball(mTextures));
	mBall = gBall.get();
	mBall->setPosition(gameView.getCenter().x, gameView.getCenter().y);
	mBall->createAnimation("roll_ball",BallTexture,sf::seconds(2),true);
	mBall->addFrames(string("roll_ball"), sf::Vector2i(0,0), sf::Vector2i(32,32),2);
	mBall->switchAnimation(string("roll_ball"));
	//
	gBall->createAnimation("ball_animation",BallTexture,sf::seconds(2),true);
	const TileSheet& sheet = mTextures.get(BallTexture);
	vector<sf::IntRect> v = sheet.getFrame("ball_animation");
	gBall->addFrames(string("ball_animation"), v);
	gBall->switchAnimation("ball_animation");
	///
	mBall->setVelocity(static_cast<float>(mWindow.getSize().x) / 5,0.000001f);
	///
	mSceneLayers[Ground]->attachChild(std::move(gBall));
	//LEFT PADDLE CREATING
	std::unique_ptr<Paddle> gLPaddle(new Paddle(RecieverType::LeftPaddle, mTextures));

	gLPaddle->createAnimation("paddle_up",PaddleTexture,sf::seconds(2),false);
	gLPaddle->addFrames(string("paddle_up"),sf::Vector2i(0,0), sf::Vector2i(25,100),1);
	gLPaddle->switchAnimation("paddle_up");

	gLPaddle->createAnimation("paddle_down",PaddleTexture,sf::seconds(2),false, true, 180);
	gLPaddle->addFrames(string("paddle_down"), sf::Vector2i(0,0), sf::Vector2i(25,100),1);
	gLPaddle->switchAnimation("paddle_down");

	sf::Vector2u tmp_sz = (*gLPaddle).getSize();
	sf::Vector2f l_pos(static_cast<float>(tmp_sz.x), static_cast<float>(mWindow.getSize().y / 2));
	gLPaddle->setPosition(l_pos);
	//
	mSceneLayers[Ground]->attachChild(std::move(gLPaddle));
	//RIGHT PADDLE CREATING
	std::unique_ptr<Paddle> gRPaddle(new Paddle(RecieverType::RightPaddle, mTextures));
	sf::Vector2f r_pos(static_cast<float>(mWindow.getSize().x - tmp_sz.x / 2), static_cast<float>(mWindow.getSize().y / 2)); 
	gRPaddle->setPosition(r_pos);

	gRPaddle->createAnimation("paddle_up",PaddleTexture,sf::seconds(2),false);
	gRPaddle->addFrames(string("paddle_up"),sf::Vector2i(0,0), sf::Vector2i(25,100),1);
	gRPaddle->switchAnimation("paddle_up");

	gRPaddle->createAnimation("paddle_down",PaddleTexture,sf::seconds(2),false, true, 180);
	gRPaddle->addFrames(string("paddle_down"), sf::Vector2i(0,0), sf::Vector2i(25,100),1);
	//gRPaddle->switchAnimation("paddle_down");
	//
	mSceneLayers[Ground]->attachChild(std::move(gRPaddle));
	//BACKGROUND CREATING
	mSceneLayers[BackGround]->attachChild(std::move(std::unique_ptr<SpriteNode>(new SpriteNode(mTextures.get(BackGroundTexture).getTexture(), 2, 2) )));
	//CUBE CREATING
	std::unique_ptr<Cube> gCube(new Cube(mTextures));
	gCube->centerOrigin();
	gCube->setPosition(100,100);
	mSceneLayers[Ground]->attachChild(std::move(gCube));
}

void World::draw()
{
	for(int i = 0; i < LayerCount; ++i)
	{
		mWindow.draw(*mSceneLayers[i]);
	}
}

void World::update(sf::Time dt)
{
	//Выполняем все команды из стека команд//
	while(!mCommandQueue.isEmpty())
	{
		for(int i = 0; i < LayerCount; ++i)
		{
			mSceneLayers[i]->onCommand(mCommandQueue.Top(), dt);
		}
		mCommandQueue.Pop();
	}
	//Обновляем все слои//
	for(int i = 0; i < LayerCount; ++i)
	{
		mSceneLayers[i]->update(dt);
	}
	//Запускаем команды, поправляющую выход ракеток за границы
	Command LeftPaddleAdopter;
	LeftPaddleAdopter.action = derivedAction<Paddle>(PositionAdopter<Paddle>(mWindow.getView()));
	LeftPaddleAdopter.category = RecieverType::LeftPaddle;
	mCommandQueue.Push(LeftPaddleAdopter);
	Command RightPaddleAdopter;
	RightPaddleAdopter.action = derivedAction<Paddle>(PositionAdopter<Paddle>(mWindow.getView()));
	RightPaddleAdopter.category = RecieverType::RightPaddle;
	mCommandQueue.Push(RightPaddleAdopter);
	///Проверка столкновений сущностей 
	handleCollisions();
	//Проверка выхода шара за пределы области
	auto pos = mBall->getPosition();
	Command ballCommand;
	ballCommand.category = RecieverType::Ball;
	ballCommand.action = derivedAction<Ball>(BallWallCollider<Ball>(mWindow.getView()));
	mCommandQueue.Push(ballCommand);
	//
	auto sz = mBall->getSize();
	auto posit = mBall->getPosition();
	auto ws = mWindow.getSize();
	if (mBall->getPosition().x - mBall->getSize().x / 2 < 0.f || mBall->getPosition().x + mBall->getSize().x / 2 > mWindow.getSize().x)
    {
		the_end = true;
    }
	//
	mSceneLayers[Ground]->removeWrecks();
}

void World::handleCollisions()
{
	std::set<SceneNode::Pair> collisions;
	mSceneLayers[Ground]->checkSceneCollision(*mSceneLayers[Ground],collisions);
	for(std::set<SceneNode::Pair>::iterator itr = collisions.begin(); itr != collisions.end(); ++itr)
	{
		SceneNode::Pair p = *itr;
		if (matchesCategories(p, NodeType::Ball, NodeType::Paddle))
		{
			Ball* t_ball = dynamic_cast<Ball*>(p.first);
			Paddle* t_paddle = dynamic_cast<Paddle*>(p.second);
			//
			float rand_ball_direction = static_cast<float>( rand() / static_cast<float>(RAND_MAX) * 0.5 * pi - 0.25 * pi);
			auto balvel = t_ball->getVelocity();
			float ball_direction;
			if(!balvel.x || !balvel.y) ball_direction = pi;
			else ball_direction = std::atan(balvel.x / balvel.y );
			t_ball->rotate_velocity(2*ball_direction + rand_ball_direction);
		}
		if (matchesCategories(p, NodeType::Ball, NodeType::Cube))
		{
			Ball* t_ball = dynamic_cast<Ball*>(p.first);
			Cube* t_cube = dynamic_cast<Cube*>(p.second);
			//
			float rand_ball_direction = static_cast<float>( rand() / static_cast<float>(RAND_MAX) * 0.5 * pi - 0.25 * pi);
			auto balvel = t_ball->getVelocity();
			float ball_direction;
			if(!balvel.x || !balvel.y) ball_direction = pi;
			else ball_direction = std::atan(balvel.x / balvel.y );
			t_ball->rotate_velocity(2*ball_direction + rand_ball_direction);
			//
			t_cube->kill();
		}
	}
}

CommandQueue& World::getCommandQueue() 
{
	return mCommandQueue;
}

bool matchesCategories(SceneNode::Pair& colliders, NodeType type1, NodeType type2)
{
	auto category1 = colliders.first->getNodeType();
	auto category2 = colliders.second->getNodeType();

	if(static_cast<unsigned int>(type1) & static_cast<unsigned int>(category1) && 
		static_cast<unsigned int>(type2) & static_cast<unsigned int>(category2)) return true;
	else if (static_cast<unsigned int>(type1) & static_cast<unsigned int>(category2) && 
		static_cast<unsigned int>(type2) & static_cast<unsigned int>(category1)) 
		{
			std::swap(colliders.first, colliders.second);
			return true;
		}
	return false;
}