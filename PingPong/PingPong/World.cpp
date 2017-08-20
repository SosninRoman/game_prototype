#include "World.h"
#include <iostream>

float pi = 3.14159f;
bool matchesCategories(SceneNode::Pair& colliders, NodeType type1, NodeType type2);

b2Body* tstBody;

World::World(sf::RenderWindow& window, TextureHolder& textures):
	mWindow(window), 
	mWorldBounds(0.f, 0.f, static_cast<float>(mWindow.getSize().x), 
	static_cast<float>(mWindow.getSize().y)), 
	the_end(false), 
	mCommandQueue(), 
	mTextures(textures),
	mPhysicWorld(b2Vec2(0,00))
{
	mPhysicWorld.SetContactListener(&mContactListener);
	buildScene();
}

void World::buildScene()
{
	mLevel.loadFromFile("res/pong_map.tmx", mTextures);
	//
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
	b2BodyDef BodyDef;
	auto posx = pixel_to_metr<double>(mBall->getPosition().x);
	auto posy = pixel_to_metr<double>(mBall->getPosition().y);
	BodyDef.position = b2Vec2(posx, posy);
    BodyDef.type = b2_dynamicBody;
    
	b2Body* Body = mPhysicWorld.CreateBody(&BodyDef);

    b2PolygonShape Shape;
	Shape.SetAsBox(pixel_to_metr<float>(mBall->getSize().x/2), pixel_to_metr<float>(mBall->getSize().y/2));
	//
	//
    
	b2FixtureDef FixtureDef;
    FixtureDef.density = 1.f;
    FixtureDef.friction = 0.7f;
    FixtureDef.shape = &Shape;	
	FixtureDef.restitution = 1;
    Body->CreateFixture(&FixtureDef);
	Body->SetUserData(gBall.get());

	Body->ApplyLinearImpulseToCenter(b2Vec2(-5, 0.f), true);

	gBall->setBody(Body);
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

	gLPaddle->centerOrigin();

	sf::Vector2u tmp_sz = (*gLPaddle).getSize();
	sf::Vector2f l_pos(static_cast<float>(tmp_sz.x) / 2, static_cast<float>(mWindow.getSize().y / 2));
	gLPaddle->setPosition(l_pos);
	//
	auto gb = gLPaddle->getGlobalBounds();
	gLPaddle->setBody(createBoxBody(12.5, 240, 25, 100, b2_kinematicBody) );
	//
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
	gRPaddle->switchAnimation("paddle_down");
	//
	auto boun = gRPaddle->getGlobalBounds();
	gRPaddle->setBody(createBoxBody(r_pos.x, r_pos.y, gRPaddle->getGlobalBounds().width, gRPaddle->getGlobalBounds().height, b2_kinematicBody) );
	//
	mSceneLayers[Ground]->attachChild(std::move(gRPaddle));
	//BACKGROUND CREATING
	//FILLING SCENE BY OBJECTS FROM THE MAP
	vector<LevelObject>& objects = mLevel.getAllObjects();
	for( auto& obj : objects)
	{
		if(obj.type == "Cube")
		{
			std::unique_ptr<Cube> map_Cube(new Cube(obj.sprite));
			sf::Rect<int> rect = obj.rect;
			map_Cube->centerOrigin();
			map_Cube->setPosition(rect.left + static_cast<double>(rect.width) / 2 , rect.top - static_cast<double>(rect.height) / 2);
			//
			map_Cube->setBody(createBoxBody(map_Cube->getPosition().x, map_Cube->getPosition().y, 
				obj.sprite.getTextureRect().height, obj.sprite.getTextureRect().width, b2_staticBody));
			//
			mSceneLayers[Ground]->attachChild(std::move(map_Cube));
		}
		if(obj.type == "Wall")
		{
			std::unique_ptr<Wall> map_Wall(new Wall());
			map_Wall->setRectangle(obj.rect);
			map_Wall->setPosition(obj.rect.left, obj.rect.top);
			//
			map_Wall->setBody(createBoxBody(obj.rect.left + obj.rect.width / 2, obj.rect.top + obj.rect.height / 2,  obj.rect.width, obj.rect.height, b2_staticBody) );
			//
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
	//test
	 //for (b2Body* BodyIterator = mPhysicWorld.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
  //      {
  //          /*if (BodyIterator->GetType() == b2_dynamicBody)
  //          {
		//		SceneNode* node = static_cast<SceneNode*>(BodyIterator->GetUserData());
		//		sf::RectangleShape Sprite;
		//		Sprite.setSize(sf::Vector2f(32,32) );
		//		Sprite.setFillColor(sf::Color::Red);
  //              Sprite.setOrigin(16.f, 16.f);
  //              Sprite.setPosition(30 * BodyIterator->GetPosition().x, 30 * BodyIterator->GetPosition().y);
  //              Sprite.setRotation(BodyIterator->GetAngle() * 180/b2_pi);
  //              mWindow.draw(Sprite);                
  //          }*/
  //          if (BodyIterator->GetType() == b2_staticBody)
  //          {
		//		sf::RectangleShape GroundSprite;
		//		GroundSprite.setSize(sf::Vector2f(32, 32));
		//		GroundSprite.setFillColor(sf::Color::Black);
  //              GroundSprite.setOrigin(16, 16.f);
		//		auto posx = BodyIterator->GetPosition().x * 30;
		//		auto posy = BodyIterator->GetPosition().y * 30;
  //              GroundSprite.setPosition(posx, posy);
  //              GroundSprite.setRotation(180/b2_pi * BodyIterator->GetAngle());
  //              mWindow.draw(GroundSprite);
  //          }
		//	if (BodyIterator->GetType() == b2_kinematicBody)
  //          {
		//		sf::RectangleShape GroundSprite;
		//		SceneNode* node = static_cast<SceneNode*>(BodyIterator->GetUserData());
		//		GroundSprite.setSize(sf::Vector2f(25, 100));
		//		GroundSprite.setFillColor(sf::Color::Green);
  //              GroundSprite.setOrigin(12.5, 50.f);
		//		auto posx = BodyIterator->GetPosition().x * 30;
		//		auto posy = BodyIterator->GetPosition().y * 30;
  //              GroundSprite.setPosition(posx, posy);
  //              GroundSprite.setRotation(180/b2_pi * BodyIterator->GetAngle());
  //              mWindow.draw(GroundSprite);
  //          }
  //      }
	//
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
	//handleCollisions();
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
			//auto balvel = t_ball->getVelocity();
			//float ball_direction;
			//if(!balvel.x || !balvel.y) ball_direction = pi;
			//else ball_direction = std::atan(balvel.x / balvel.y );
			//t_ball->rotate_velocity(2*ball_direction + rand_ball_direction);
		}
		if (matchesCategories(p, NodeType::Ball, NodeType::Cube))
		{
			Ball* t_ball = dynamic_cast<Ball*>(p.first);
			Cube* t_cube = dynamic_cast<Cube*>(p.second);
			//
			//float rand_ball_direction = static_cast<float>( rand() / static_cast<float>(RAND_MAX) * 0.5 * pi - 0.25 * pi);
			//auto balvel = t_ball->getVelocity();
			//float ball_direction;
			//if(!balvel.x || !balvel.y) ball_direction = pi;
			//else ball_direction = std::atan(balvel.x / balvel.y );
			//t_ball->rotate_velocity(2*ball_direction + rand_ball_direction);
			//
			t_cube->kill();
		}
		if (matchesCategories(p, NodeType::Ball, NodeType::Wall))
		{
			Ball* t_ball = dynamic_cast<Ball*>(p.first);
			Cube* t_wall = dynamic_cast<Cube*>(p.second);
			//
			//float rand_ball_direction = static_cast<float>( rand() / static_cast<float>(RAND_MAX) * 0.5 * pi - 0.25 * pi);
			//auto balvel = t_ball->getVelocity();
			//t_ball->setVelocity(balvel.x, -balvel.y);
		}
		if (matchesCategories(p, NodeType::Paddle, NodeType::Wall))
		{
			Paddle* t_paddle = dynamic_cast<Paddle*>(p.first);
			Wall* t_wall = dynamic_cast<Wall*>(p.second);
			//auto balvel = t_paddle->getVelocity();
			sf::FloatRect p_rect = t_paddle->getGlobalBounds();
			sf::FloatRect w_rect = t_wall->getGlobalBounds();
			if(w_rect.top - p_rect.top < 0)
			{
				float delta = w_rect.height - (p_rect.top - w_rect.top);
				t_paddle->move(0, delta );
			}
			else
			{
				float delta = p_rect.top + p_rect.height - w_rect.top;
				t_paddle->move(0,- delta );
			}
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

b2Body* World::createBoxBody(float pos_x, float pos_y, float height, float width, b2BodyType type)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(pixel_to_metr(pos_x), pixel_to_metr(pos_y));
	BodyDef.type = type;

	b2Body* Body = mPhysicWorld.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox(pixel_to_metr(height / 2), pixel_to_metr(width / 2) );

	b2FixtureDef fixDef;
	fixDef.density = 0.f;
	fixDef.shape = &Shape;

	Body->CreateFixture(&fixDef);
	return Body;
}

