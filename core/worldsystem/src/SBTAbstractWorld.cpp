//
// Created by G750 on 15.11.2017.
//

#include "SBTAbstractWorld.h"

SBTAbstractWorld::SBTAbstractWorld(int layers, SBTGameWindow& window, TextureHolder& textures, sf::FloatRect bounds,
                                   SBTBasicContactListener* listener, b2Vec2 worldparam, SBTCommandQueue* commandqueue):
        mSceneLayers(layers),
        mWindow(window),
        mWorldBounds(bounds),
        mCommandQueue(commandqueue),
        mTextures(textures),
        mPhysicWorld(worldparam),
        mContactListener(listener)
{
    mPhysicWorld.SetContactListener(mContactListener.get() );
}

void SBTAbstractWorld::draw()
{
    mLevel.draw(mWindow);

    for(int i = 0; i < layerCount(); ++i)
    {
        mWindow.draw(*mSceneLayers[i]);
    }
}

void SBTAbstractWorld::update(sf::Time dt)
{
    prefix();

    mPhysicWorld.Step(1/60.f, 8, 3);

    while(!mCommandQueue->isEmpty())
    {
        for(int i = 0; i < layerCount(); ++i)
        {
            mSceneLayers[i]->onCommand(mCommandQueue->Top(), dt);
        }
        mCommandQueue->Pop();
    }

    for(int i = 0; i < layerCount(); ++i)
    {
        mSceneLayers[i]->update(dt);
    }

    produceAndPushCommands();

    postfix();
}

SBTCommandQueue& SBTAbstractWorld::getCommandQueue()
{
    return *mCommandQueue;
}

bool SBTAbstractWorld::matchesCategories(SBTAbstractSceneNode::Pair& colliders, int type1, int type2, b2Contact* contact)
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

b2Body* SBTAbstractWorld::createBoxBody(float pos_x, float pos_y, float height, float width, b2BodyType type, float dens, bool fixRotation)
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

b2Body* SBTAbstractWorld::createCircleBody(float pos_x, float pos_y, float r, b2BodyType type, float dens)
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

SBTGameWindow& SBTAbstractWorld::getWindow() const
{
    return mWindow;
}

int SBTAbstractWorld::layerCount()
{
    return 0;
}

void SBTAbstractWorld::loadLevel(std::string filepath)
{
    mLevel.loadFromFile(filepath, mTextures);
}

SBTLevel& SBTAbstractWorld::getLevel()
{
    return mLevel;
}

SBTAbstractSceneNode::Ptr& SBTAbstractWorld::getSceneLayer(size_t i)
{
    return mSceneLayers[i];
}

TextureHolder& SBTAbstractWorld::getTextures()
{
    return mTextures;
}