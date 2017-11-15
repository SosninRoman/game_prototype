//
// Created by G750 on 15.11.2017.
//

#include "MyContactListener.h"
#include "World.h"

myContactListener::myContactListener(World* world):
SBTBasicContactListener(world)
{
}

void myContactListener::BeginContact(b2Contact* contact)
{
    SBTAbstractSceneNode::Pair p(static_cast<SBTAbstractSceneNode*>(contact->GetFixtureA()->GetBody()->GetUserData()),
                      static_cast<SBTAbstractSceneNode*>(contact->GetFixtureB()->GetBody()->GetUserData()) );
    if (getWorld()->matchesCategories(p, NodeType::BallNodeType, NodeType::PaddleNodeType, contact))
    {
        Ball* t_ball = dynamic_cast<Ball*>(p.first);
        Paddle* t_paddle = dynamic_cast<Paddle*>(p.second);
        t_ball->setMaster(t_paddle->getActionType());
    }
}

void myContactListener::EndContact(b2Contact* contact)
{
    SBTAbstractSceneNode::Pair p(static_cast<SBTAbstractSceneNode*>(contact->GetFixtureA()->GetBody()->GetUserData()),
                      static_cast<SBTAbstractSceneNode*>(contact->GetFixtureB()->GetBody()->GetUserData()) );
    if (getWorld()->matchesCategories(p, NodeType::BallNodeType, NodeType::CubeNodeType, contact))
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
    if (getWorld()->matchesCategories(p, NodeType::BallNodeType, NodeType::PaddleNodeType, contact))
    {
        Ball* t_ball = dynamic_cast<Ball*>(p.first);
        b2Vec2 v = t_ball->getBody()->GetLinearVelocity();
        auto l = v.Length();
        v.x = v.x / l * 5;
        v.y = v.y / l * 5;
        l = v.Length();
        t_ball->getBody()->SetLinearVelocity(v);
    }
    if (getWorld()->matchesCategories(p, NodeType::BallNodeType, NodeType::WallNodeType, contact))
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

void myContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
    SBTAbstractSceneNode::Pair p(static_cast<SBTAbstractSceneNode*>(contact->GetFixtureA()->GetBody()->GetUserData()),
                      static_cast<SBTAbstractSceneNode*>(contact->GetFixtureB()->GetBody()->GetUserData()) );
    if (getWorld()->matchesCategories(p, NodeType::BallNodeType, NodeType::PaddleNodeType, contact))
    {
        Ball* t_ball = dynamic_cast<Ball*>(p.first);
        Cube* t_paddle = dynamic_cast<Cube*>(p.second);
        b2Vec2 v;
    }
}