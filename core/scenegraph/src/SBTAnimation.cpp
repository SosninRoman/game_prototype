//
// Created by G750 on 19.11.2017.
//

#include "SBTAnimation.h"

void SBTAnimation::AddFrames(sf::Vector2i startFrom, const sf::Vector2i& frameSize, size_t frames)
{
    for(size_t i = 0; i < frames; ++i)
    {
        mFrames.emplace_back(sf::IntRect(startFrom.x, startFrom.y, frameSize.x, frameSize.y));
        startFrom.x += frameSize.x;
    }
}

void SBTAnimation::AddFrames(std::vector<sf::IntRect> frames)
{
    mFrames.assign(frames.begin(), frames.end());
}