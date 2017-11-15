//
// Created by G750 on 19.11.2017.
//

#ifndef GAME_PROTOTYPE_SBTANIMATION_H
#define GAME_PROTOTYPE_SBTANIMATION_H
#include <SFML\Graphics.hpp>
#include <vector>
#include "ResourceHolder.h"
#include "SBTTileSheet.h"

struct SBTAnimation
{
    int				mTextureID;

    sf::Time				mDuration;

    bool					mLooping;

    std::vector<sf::IntRect>		mFrames;

    bool                    mRotation;

    float                   mAngle;

    SBTAnimation(int textureID, sf::Time& duration, bool looping, bool rotate = false, float degree = 0):
            mTextureID(textureID),
            mDuration(duration),
            mLooping(looping),
            mRotation(rotate),
            mAngle(degree)
    {
    }

    void AddFrames(sf::Vector2i startFrom, const sf::Vector2i& frameSize, size_t frames);

    void AddFrames(std::vector<sf::IntRect> frames);
};

#endif //GAME_PROTOTYPE_SBTANIMATION_H
