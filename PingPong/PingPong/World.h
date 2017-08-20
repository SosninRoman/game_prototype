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
		virtual ~myContactListener() {}

		virtual void BeginContact(b2Contact* contact) 
		{ 
			if(contact->GetFixtureA()->GetBody()->GetType() == b2_kinematicBody)
			{
				b2Body* Body = contact->GetFixtureA()->GetBody();
				SceneNode* node = static_cast<SceneNode*>(Body->GetUserData());
				auto posx = Body->GetPosition().x * 30;
				auto posy = Body->GetPosition().y * 30;
				int a = 1;
			}
			if(contact->GetFixtureB()->GetBody()->GetType() == b2_kinematicBody)
			{
				b2Body* Body = contact->GetFixtureB()->GetBody();
				SceneNode* node = static_cast<SceneNode*>(Body->GetUserData());
				b2WorldManifold worldManifold;
				contact->GetWorldManifold( &worldManifold );
				auto posx = Body->GetPosition().x * 30;
				auto posy = Body->GetPosition().y * 30;
				auto sz = Body->GetWorldCenter();
				int a = 1;
			}
		}

		virtual void EndContact(b2Contact* contact) 
		{ 
			
		}

		virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
		{
			
		}

		virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
		{
			
		}
	};
public:
	enum Layer
	{
		BackGround,
		Ground,
		LayerCount
	};
	World(sf::RenderWindow& window, TextureHolder& textures);
	
	void			draw();
	void			update(sf::Time dt);
	//
	void			handleEvent(const sf::Event& event);
	bool			theEnd(){return the_end;}

	CommandQueue&	getCommandQueue() ;
	void			handleCollisions();

	
private:
	std::array<SceneNode::Ptr, LayerCount>	mSceneLayers;
	sf::RenderWindow&						mWindow;
	sf::FloatRect							mWorldBounds;

	void									buildScene();

	bool									the_end;
	Ball*									mBall;

	CommandQueue							mCommandQueue;

	TextureHolder&							mTextures;

	Level									mLevel;

	b2World									mPhysicWorld; 

	b2Body*									createBoxBody(float pos_x, float pos_y, float height, float width, b2BodyType type);
	myContactListener						mContactListener;
};

