//
// Created by G750 on 15.11.2017.
//

#ifndef GAME_PROTOTYPE_SBTABSTRACTCONTACTLISTENER_H
#define GAME_PROTOTYPE_SBTABSTRACTCONTACTLISTENER_H
#include <Box2D\Box2D.h>

class SBTAbstractWorld;

class SBTBasicContactListener: public b2ContactListener
{
public:
    SBTBasicContactListener(SBTAbstractWorld* world)
    {
        myWorld = world;
    }

    virtual ~SBTBasicContactListener() = default;

    void BeginContact(b2Contact* contact) override {}

    virtual void EndContact(b2Contact* contact) override {}

    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override {}

    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override {}

    SBTAbstractWorld* getWorld(){return myWorld;}
private:
    SBTAbstractWorld* myWorld;
};

#endif //GAME_PROTOTYPE_SBTABSTRACTCONTACTLISTENER_H
