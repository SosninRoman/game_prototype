//
// Created by G750 on 19.11.2017.
//

#ifndef GAME_PROTOTYPE_GAMEOVERSTATEPARAM_H
#define GAME_PROTOTYPE_GAMEOVERSTATEPARAM_H
#include "SBTAbstractApplicationState.h"
#include "RecieverTypeEnum.h"

struct GameOverParam: public StateCreationParam
{
    GameOverParam(RecieverType type): mWinnerType(type) {}
    virtual ~GameOverParam() {}
    RecieverType mWinnerType;
};
#endif //GAME_PROTOTYPE_GAMEOVERSTATEPARAM_H
