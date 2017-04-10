#include "World.h"
#include <iostream>

float pi = 3.14159f;
bool matchesCategories(SceneNode::Pair& colliders, NodeType type1, NodeType type2);

World::World(sf::RenderWindow& window):
	mWindow(window), mWorldBounds(0.f, 0.f, static_cast<float>(mWindow.getSize().x), static_cast<float>(mWindow.getSize().y)), the_end(false), mCommandQueue()
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
	//
	std::unique_ptr<Ball> gBall(new Ball(sf::CircleShape(10.f)));
	mBall = gBall.get();
	mBall->setOutlineColor(sf::Color::Black);
	mBall->setOutlineThickness(1);
	mBall->setFillColor(sf::Color::White);
	mBall->setOrigin(sf::Vector2f(mBall->getSize() / 2, mBall->getSize() / 2));
	mBall->setPosition(gameView.getCenter().x, gameView.getCenter().y);
	///
	mBall->setVelocity(static_cast<float>(mWindow.getSize().x) / 5,0.000001f);
	///
	mSceneLayers[Ground]->attachChild(std::move(gBall));
	//
	std::unique_ptr<Paddle> gLPaddle(new Paddle(sf::RectangleShape(sf::Vector2f(25,100)),RecieverType::LeftPaddle));
	sf::Vector2f tmp_sz = (*gLPaddle).getSize();
	mLeftPaddle = gLPaddle.get();
	mLeftPaddle->setOrigin(tmp_sz.x / 2, tmp_sz.y / 2);
	sf::Vector2f l_pos(static_cast<float>(tmp_sz.x), static_cast<float>(mWindow.getSize().y / 2));
	mLeftPaddle->setPosition(l_pos);
	mLeftPaddle->setOutlineThickness(1);
	mLeftPaddle->setOutlineColor(sf::Color::Black);
	mLeftPaddle->setFillColor(sf::Color::Red);
	//
	mSceneLayers[Ground]->attachChild(std::move(gLPaddle));
	//
	std::unique_ptr<Paddle> gRPaddle(new Paddle(sf::RectangleShape(sf::Vector2f(25,100)),RecieverType::RightPaddle));
	mRightPaddle = gRPaddle.get();
	mRightPaddle->setOrigin(tmp_sz.x / 2, tmp_sz.y / 2);
	sf::Vector2f r_pos(static_cast<float>(mWindow.getSize().x - tmp_sz.x / 2), static_cast<float>(mWindow.getSize().y / 2)); 
	mRightPaddle->setPosition(r_pos);
	mRightPaddle->setOutlineThickness(1);
	mRightPaddle->setOutlineColor(sf::Color::Black);
	mRightPaddle->setFillColor(sf::Color::Green);
	mSceneLayers[Ground]->attachChild(std::move(gRPaddle));
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
	/*sf::FloatRect b = mBall->getGlobalBounds();
	std::cout << b.top << ' ' << b.left << ' ' << b.height << ' ' << b.width << '\n';

	if (mBall->getGlobalBounds().intersects(mLeftPaddle->getGlobalBounds())) 
	{
		float rand_ball_direction = static_cast<float>(rand() / static_cast<float>(RAND_MAX) * 0.5 * pi - 0.25 * pi);
		auto balvel = mBall->getVelocity();
		float ball_direction;
		if(!balvel.x || !balvel.y) ball_direction = pi;
		else ball_direction = std::atan(balvel.x / balvel.y);
		mBall->rotate_velocity(2*ball_direction + rand_ball_direction);
	}
	if (mBall->getGlobalBounds().intersects(mRightPaddle->getGlobalBounds())) 
	{
		float rand_ball_direction = static_cast<float>( rand() / static_cast<float>(RAND_MAX) * 0.5 * pi - 0.25 * pi);
		auto balvel = mBall->getVelocity();
		float ball_direction;
		if(!balvel.x || !balvel.y) ball_direction = pi;
		else ball_direction = std::atan(balvel.x / balvel.y );
		mBall->rotate_velocity(2*ball_direction + rand_ball_direction);
	}*/
	//Проверка выхода шара за пределы области
	auto pos = mBall->getPosition();
	Command ballCommand;
	ballCommand.category = RecieverType::Ball;
	ballCommand.action = derivedAction<Ball>(BallWallCollider<Ball>(mWindow.getView()));
	mCommandQueue.Push(ballCommand);
	//
	if (mBall->getPosition().x - mBall->getSize() < 0.f || mBall->getPosition().x + mBall->getSize() > mWindow.getSize().x)
    {
		the_end = true;
    }
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