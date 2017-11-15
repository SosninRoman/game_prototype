//
// Created by G750 on 15.11.2017.
//

#ifndef GAME_PROTOTYPE_SBTABSTRACTWORLD_H
#define GAME_PROTOTYPE_SBTABSTRACTWORLD_H

#pragma once
#include <array>
#include <SFML\Graphics.hpp>
#include "SBTAbstractSceneNode.h"
#include "SBTAbstractSpriteNode.h"
#include "SBTCommandQueue.h"
//#include "CommandCatalogue.h"
#include "ResourceHolder.h"
#include "SBTLevel.h"
#include "SBTGameWindow.h"
#include <Box2D\Box2D.h>
#include "SBTBasicContactListener.h"

class SBTAbstractWorld: public sf::NonCopyable
{

public:

    SBTAbstractWorld(int layers, SBTGameWindow& window, TextureHolder& textures, sf::FloatRect bounds, SBTBasicContactListener* listener,
                     b2Vec2 worldparam, SBTCommandQueue* commandqueue);

    void									    draw();

    virtual void								update(sf::Time dt);

    SBTCommandQueue&							    getCommandQueue() ;

    SBTGameWindow&							        getWindow() const;

    SBTLevel&                                      getLevel();

    SBTAbstractSceneNode::Ptr&                             getSceneLayer(size_t i);

    TextureHolder&                              getTextures();

    bool									    matchesCategories(SBTAbstractSceneNode::Pair& colliders, int type1, int type2, b2Contact* contact = nullptr);

    virtual void                                prefix(){};

    virtual void                                postfix() {};

    virtual void                                produceAndPushCommands() = 0;

    virtual int                        layerCount();

    virtual void                                loadLevel(std::string filepath);
protected:
    b2Body*									    createBoxBody(float pos_x, float pos_y, float height, float width, b2BodyType type, float dens = 0.f, bool fixRotation = false);

    b2Body*									    createCircleBody(float pos_x, float pos_y, float r, b2BodyType type, float dens = 0.f);
private:
    virtual void							    buildScene() = 0;

    //data
    std::vector<SBTAbstractSceneNode::Ptr>	                mSceneLayers;

    SBTGameWindow&								    mWindow;

    sf::FloatRect							    mWorldBounds;

    std::unique_ptr<SBTCommandQueue>			    mCommandQueue;

    TextureHolder&							    mTextures;

    SBTLevel									    mLevel;

    b2World									    mPhysicWorld;

    std::unique_ptr<SBTBasicContactListener>	mContactListener;
};


#endif //GAME_PROTOTYPE_SBTABSTRACTWORLD_H
