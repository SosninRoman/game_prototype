//
// Created by G750 on 19.11.2017.
//

#ifndef GAME_PROTOTYPE_RECIEVERTYPEENUM_H
#define GAME_PROTOTYPE_RECIEVERTYPEENUM_H

enum RecieverType
{
    NoneRecieverType = 0,
    SceneRecieverType = 1,
    LeftPaddleRecieverType = 1 << 1,
    RightPaddleRecieverType = 1 << 2,
    BallRecieverType = 1 << 3,
    CubeRecieverType = 1 << 4,
    WallRecieverType = 1 << 5,
};

#endif //GAME_PROTOTYPE_RECIEVERTYPEENUM_H
