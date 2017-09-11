#include "World.h"
#include <iostream>

float pi = 3.14159f;

b2Body* tstBody;

World::World(sf::RenderWindow& window, TextureHolder& textures):
	mWindow(window), 
	mWorldBounds(0.f, 0.f, static_cast<float>(mWindow.getSize().x), 
	static_cast<float>(mWindow.getSize().y)), 
	the_end(false), 
	mCommandQueue(), 
	mTextures(textures),
	mPhysicWorld(b2Vec2(0,00)),
	mContactListener(this)
{
	mPhysicWorld.SetContactListener(&mContactListener);
	
	buildScene();
}

World::~World()
{
}

void World::buildScene()
{
	mLevel.loadFromFile("../res/pong_map.tmx", mTextures);
	//
	for(int i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = std::move(layer);
	}
	sf::View gameView = mWindow.getView();	
	
	//BALL CREATING
	sf::Vector2f ball_center(gameView.getCenter().x, gameView.getCenter().y);
	
	std::unique_ptr<Ball> gBall( new Ball(mTextures, ball_center) );

	gBall->createAnimation("ball_animation", BallTexture, sf::seconds(2), false);
	
	gBall->addFrames(string("ball_animation"),sf::Vector2i(0,0), sf::Vector2i(25,25),1);
	
	gBall->switchAnimation("ball_animation");

	b2Body* Body = createCircleBody(gBall->getPosition().x, gBall->getPosition().y, gBall->getSize().x/2, b2_dynamicBody, 1.f);

	Body->SetLinearVelocity(b2Vec2(-5, 0.f));

	gBall->setBody(Body);

	mSceneLayers[Ground]->attachChild(std::move(gBall));
	
	//LEFT PADDLE CREATING
	std::unique_ptr<Paddle> gLPaddle(new Paddle(RecieverType::LeftPaddle, mTextures));

	gLPaddle->createAnimation("paddle_up",PaddleTexture,sf::seconds(2),false);
	
	gLPaddle->addFrames(string("paddle_up"),sf::Vector2i(0,0), sf::Vector2i(25,128),1);
	
	gLPaddle->switchAnimation("paddle_up");

	gLPaddle->createAnimation("paddle_down",PaddleTexture,sf::seconds(2),false, true, 180);
	
	gLPaddle->addFrames(string("paddle_down"), sf::Vector2i(0,0), sf::Vector2i(25,128),1);
	
	gLPaddle->switchAnimation("paddle_down");

	gLPaddle->centerOrigin();

	sf::Vector2u tmp_sz = (*gLPaddle).getSize();
	
	sf::Vector2f l_pos(static_cast<float>(tmp_sz.x) / 2, static_cast<float>(mWindow.getSize().y / 2));
	
	gLPaddle->setPosition(l_pos);

	auto gLbounds = gLPaddle->getGlobalBounds();
	
	gLPaddle->setBody(createBoxBody(l_pos.x, l_pos.y, gLbounds.width, gLbounds.height, b2_dynamicBody, 10000, true) );

	mSceneLayers[Ground]->attachChild(std::move(gLPaddle));
	
	//RIGHT PADDLE CREATING
	std::unique_ptr<Paddle> gRPaddle(new Paddle(RecieverType::RightPaddle, mTextures));
	
	sf::Vector2f r_pos(static_cast<float>(mWindow.getSize().x - tmp_sz.x / 2), static_cast<float>(mWindow.getSize().y / 2)); 
	
	gRPaddle->setPosition(r_pos);

	gRPaddle->createAnimation("paddle_up",PaddleTexture,sf::seconds(2),false);
	
	gRPaddle->addFrames(string("paddle_up"),sf::Vector2i(0,0), sf::Vector2i(25,128),1);
	
	gRPaddle->switchAnimation("paddle_up");

	gRPaddle->createAnimation("paddle_down",PaddleTexture,sf::seconds(2),false, true, 180);
	
	gRPaddle->addFrames(string("paddle_down"), sf::Vector2i(0,0), sf::Vector2i(25,128),1);
	
	gRPaddle->switchAnimation("paddle_down");

	auto gRbounds = gRPaddle->getGlobalBounds();
	
	gRPaddle->setBody(createBoxBody(r_pos.x, r_pos.y, gRbounds.width, gRbounds.height, b2_dynamicBody, 10000, true) );

	mSceneLayers[Ground]->attachChild(std::move(gRPaddle));
	
	//FILLING SCENE BY OBJECTS FROM THE MAP
	vector<LevelObject>& objects = mLevel.getAllObjects();
	
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

			mSceneLayers[Ground]->attachChild(std::move(map_Cube));
		}
		if(obj.type == "Wall")
		{
			std::unique_ptr<Wall> map_Wall(new Wall());
			
			map_Wall->setRectangle(obj.rect);
			
			map_Wall->setPosition(obj.rect.left, obj.rect.top);

			map_Wall->setBody(createBoxBody(obj.rect.left + obj.rect.width / 2, obj.rect.top + obj.rect.height / 2,  obj.rect.width, obj.rect.height, b2_staticBody) );

			mSceneLayers[Ground]->attachChild(std::move(map_Wall));
		}
	}
}

void World::draw()
{
	mLevel.draw(mWindow);

	for(int i = 0; i < LayerCount; ++i)
	{
		mWindow.draw(*mSceneLayers[i]);
	}	
}

void World::update(sf::Time dt)
{
	//Обновляем физику
	mPhysicWorld.Step(1/60.f, 8, 3);
	
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
	
	//Запускаем команды реакций объектов на мир
	Command LeftPaddleAdopter;
	
	LeftPaddleAdopter.action = derivedAction<Paddle>(PositionAdopter<Paddle>(mWindow.getView()));
	
	LeftPaddleAdopter.category = RecieverType::LeftPaddle;
	
	mCommandQueue.Push(LeftPaddleAdopter);
	
	Command RightPaddleAdopter;
	
	RightPaddleAdopter.action = derivedAction<Paddle>(PositionAdopter<Paddle>(mWindow.getView()));
	
	RightPaddleAdopter.category = RecieverType::RightPaddle;
	
	mCommandQueue.Push(RightPaddleAdopter);

	Command CheckEnd;
	
	CheckEnd.action = derivedAction<Ball>(CheckEndOfGame<Ball, World>(this));
	
	CheckEnd.category = RecieverType::Ball;
	
	mCommandQueue.Push(CheckEnd);
	
	//Очистка помеченых на удаление объектов	
	mSceneLayers[Ground]->removeWrecks();
}

CommandQueue& World::getCommandQueue() 
{
	return mCommandQueue;
}

bool World::matchesCategories(SceneNode::Pair& colliders, NodeType type1, NodeType type2, b2Contact* contact)
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

b2Body* World::createBoxBody(float pos_x, float pos_y, float height, float width, b2BodyType type, float dens, bool fixRotation)
{
	b2BodyDef BodyDef;
	
	BodyDef.position = b2Vec2(pixel_to_metr(pos_x), pixel_to_metr(pos_y));
	
	BodyDef.type = type;

	BodyDef.fixedRotation = fixRotation;

	b2Body* Body = mPhysicWorld.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	
	Shape.SetAsBox(pixel_to_metr(height / 2), pixel_to_metr(width / 2) );

	b2FixtureDef fixDef;
	
	fixDef.density = dens;
	
	fixDef.shape = &Shape;
	
	fixDef.restitution = 1;
	
	Body->SetLinearDamping(0);

	Body->CreateFixture(&fixDef);
	
	return Body;
}

b2Body* World::createCircleBody(float pos_x, float pos_y, float r, b2BodyType type, float dens)
{
	b2BodyDef BodyDef;
	
	BodyDef.position = b2Vec2(pixel_to_metr<double>(pos_x), pixel_to_metr<double>(pos_y));
	
	BodyDef.type = type;

	b2Body* Body = mPhysicWorld.CreateBody(&BodyDef);

	b2CircleShape Shape;
	
	Shape.m_radius = pixel_to_metr<double>(r);

	b2FixtureDef fixDef;
	
	fixDef.density = dens;
	
	fixDef.shape = &Shape;
	
	fixDef.restitution = 1;
	
	fixDef.friction = 0.7;
	
	Body->SetLinearDamping(0);

	Body->CreateFixture(&fixDef);
	
	return Body;
}

sf::RenderWindow& World::getWindow() const
{
	return mWindow;
}

void World::setEndGame()
{
	the_end = true;
}