//
// Created by G750 on 12.11.2017.
//

#include "SBTAbstractCommandManager.h"

void SBTAbstractCommandManager::setCommand(int id, std::function<void (SBTAbstractSceneNode&, sf::Time)> action, int category)
{
    mActions[id].action = action;
    mActions[id].category = category;
}

void SBTAbstractCommandManager::setActionToKeyboard(sf::Keyboard::Key key, int id)
{
    mKeyBinding[key]   =    id;
}

SBTCommand SBTAbstractCommandManager::getCommand(int id)
{
    return mActions[id];
}

void SBTAbstractCommandManager::handleRealtimeInput(SBTCommandQueue& commands)
{
    std::for_each(mKeyBinding.begin(), mKeyBinding.end(),
                  [&commands, this](const std::pair<sf::Keyboard::Key, int>& pair)
                  {
                      if(sf::Keyboard::isKeyPressed(pair.first) && this->isRealtimeAction(pair.second))
                          commands.Push(mActions[pair.second]);
                  }
    );
}