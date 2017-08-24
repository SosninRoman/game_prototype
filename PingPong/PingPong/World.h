#pragma once
#include <array>
#include <SFML\Graphics.hpp>
#include "SceneNode.h"
#include "Ball.h"
#include "Paddle.h"
#include "Cube.h"
#include "Wall.h"
#include "SpriteNode.h"
#include "CommandQueue.h"
#include "CommandCatalogue.h"
#include "ResourceHolder.h"
#include "Level.h"
#include <Box2D\Box2D.h>

class World: public sf::NonCopyable
{
	class myContactListener: public b2ContactListener
	{
	public:
		myContactListener(World* world)
		{
			myWorld = world;
		}
		virtual ~myContactListener() {}

		virtual void BeginContact(b2Contact* contact) 
		{ 
			SceneNode::Pair p(static_cast<SceneNode*>(contact->GetFixtureA()->GetBody()->GetUserData()),
				static_cast<SceneNode*>(contact->GetFixtureB()->GetBody()->GetUserData()) );
			if (myWorld->matchesCategories(p, NodeType::Ball, NodeType::Paddle, contact))
			{
				Ball* t_ball = dynamic_cast<Ball*>(p.first);
				Cube* t_paddle = dynamic_cast<Cube*>(p.second);
				t_ball->setMaster(t_paddle->getActionType());
			}
		}

		virtual void EndContact(b2Contact* contact) 
		{ 
			SceneNode::Pair p(static_cast<SceneNode*>(contact->GetFixtureA()->GetBody()->GetUserData()),
				static_cast<SceneNode*>(contact->GetFixtureB()->GetBody()->GetUserData()) );
			if (myWorld->matchesCategories(p, NodeType::Ball, NodeType::Cube, contact))
			{
				Ball* t_ball = dynamic_cast<Ball*>(p.first);
				Cube* t_cube = dynamic_cast<Cube*>(p.second);
				t_cube->kill();
				b2Vec2 v = t_ball->getBody()->GetLinearVelocity();
				auto l = v.Length();
				v.x = v.x / l * 5;
				v.y = v.y / l * 5;
				l = v.Length();
				t_ball->getBody()->SetLinearVelocity(v);
			}
			if (myWorld->matchesCategories(p, NodeType::Ball, NodeType::Paddle, contact))
			{
				Ball* t_ball = dynamic_cast<Ball*>(p.first);
				b2Vec2 v = t_ball->getBody()->GetLinearVelocity();
				auto l = v.Length();
				v.x = v.x / l * 5;
				v.y = v.y / l * 5;
				l = v.Length();
				t_ball->getBody()->SetLinearVelocity(v);
			}
			if (myWorld->matchesCategories(p, NodeType::Ball, NodeType::Wall, contact))
			{
				Ball* t_ball = dynamic_cast<Ball*>(p.first);
				b2Vec2 v = t_ball->getBody()->GetLinearVelocity();
				auto l = v.Length();
				v.x = v.x / l * 5;
				v.y = v.y / l * 5;
				l = v.Length();
				t_ball->getBody()->SetLinearVelocity(v);
			}
		}

		virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
		{
			
		}

		virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
		{
			SceneNode::Pair p(static_cast<SceneNode*>(contact->GetFixtureA()->GetBody()->GetUserData()),
				static_cast<SceneNode*>(contact->GetFixtureB()->GetBody()->GetUserData()) );
			if (myWorld->matchesCategories(p, NodeType::Ball, NodeType::Paddle, contact))
			{
				Ball* t_ball = dynamic_cast<Ball*>(p.first);
				Cube* t_paddle = dynamic_cast<Cube*>(p.second);
				b2Vec2 v;
				//p.second->getBody()->SetLinearVelocity(b2Vec2_zero);
			}
		}
	private:
		World* myWorld;
	};
public:
	enum Layer
	{
		BackGround,
		Ground,
		LayerCount
	};
	World(sf::RenderWindow& window, TextureHolder& textures);
	~World();
	
	void									draw();
	void									update(sf::Time dt);
	//
	void									handleEvent(const sf::Event& event);
	bool									theEnd(){return the_end;}

	CommandQueue&							getCommandQueue() ;
	void									handleCollisions();
	sf::RenderWindow&						getWindow() const;

	bool									matchesCategories(SceneNode::Pair& colliders, NodeType type1, NodeType type2, b2Contact* contact = nullptr);
	void									setEndGame();
private:
	std::array<SceneNode::Ptr, LayerCount>	mSceneLayers;
	sf::RenderWindow&						mWindow;
	sf::FloatRect							mWorldBounds;

	void									buildScene();

	bool									the_end;

	CommandQueue							mCommandQueue;

	TextureHolder&							mTextures;

	Level									mLevel;

	b2World									mPhysicWorld; 

	b2Body*									createBoxBody(float pos_x, float pos_y, float height, float width, b2BodyType type, float dens = 0.f);
	b2Body*									createCircleBody(float pos_x, float pos_y, float r, b2BodyType type, float dens = 0.f);
	myContactListener						mContactListener;

	
};

