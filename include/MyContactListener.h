//
// Created by G750 on 15.11.2017.
//

#ifndef GAME_PROTOTYPE_MYCONTACTLISTENER_H
#define GAME_PROTOTYPE_MYCONTACTLISTENER_H

#include "SBTBasicContactListener.h"
#include "SBTAbstractSceneNode.h"
#include "Ball.h"
#include "Cube.h"
#include "Paddle.h"

class World;

class myContactListener: public SBTBasicContactListener
{
public:
    myContactListener(World* world);

    void BeginContact(b2Contact* contact) override;

    void EndContact(b2Contact* contact) override;

    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
};
#endif //GAME_PROTOTYPE_MYCONTACTLISTENER_H
