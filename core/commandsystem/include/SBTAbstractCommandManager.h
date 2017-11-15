//
// Created by G750 on 12.11.2017.
//

#ifndef GAME_PROTOTYPE_SBTEVENTMANAGER_H
#define GAME_PROTOTYPE_SBTEVENTMANAGER_H

#include <map>
#include "SBTCommandQueue.h"
#include <SFML\Graphics.hpp>
#include "SBTCommand.h"
#include "SBTAbstractSceneNode.h"

class SBTAbstractCommandManager
{
public:
    SBTAbstractCommandManager() = default;
    virtual ~SBTAbstractCommandManager() = default;
public:
    virtual void handleEvent(const sf::Event& event, SBTCommandQueue& commands) = 0;
    virtual void handleRealtimeInput(SBTCommandQueue& commands);

    virtual bool isRealtimeAction(int type) const = 0;
    virtual void InitializeCommands() = 0;

protected:
    void setCommand(int id, std::function<void (SBTAbstractSceneNode&, sf::Time)> action, int category);
    void setActionToKeyboard(sf::Keyboard::Key key, int id);

    SBTCommand getCommand(int id);
private:
    std::map<int ,SBTCommand>           mActions;
    std::map<sf::Keyboard::Key, int> mKeyBinding;
};

#endif //GAME_PROTOTYPE_SBTEVENTMANAGER_H
