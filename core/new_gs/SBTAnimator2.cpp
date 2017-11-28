//
// Created by G750 on 29.11.2017.
//

#include "SBTAnimator2.h"
//#include "SBTAnimation2.h"
#include "SBTFrame.h"

SBTAnimator2::SBTAnimator2(AtlasesHolder& textures):
        m_textures(textures), m_currentAnimation(m_animations.end())
{
}

void SBTAnimator2::addAnimation(const animationID& animationNameInAnimator, const string& sequenceIDInAtlas,
                           const std::string& SpriteAtlasID, sf::Time duration, bool looping)
{
    const SBTSpriteAtlas& atlas = m_textures.get(SpriteAtlasID);
    const SBTSpriteSequence& seq = atlas.getSequence(sequenceIDInAtlas);
    SBTAnimation anim(&seq, duration, looping);
    auto itr = m_animations.insert(make_pair(animationNameInAnimator, anim) );
    if(!itr.second)
        throw std::runtime_error("animation " + animationNameInAnimator +" already exist in animator \"" );
}

void SBTAnimator2::switchAnimation(const string& animationNameInAnimator)
{
    m_currentAnimation = m_animations.find(animationNameInAnimator);
    if(m_currentAnimation == m_animations.end() )
        throw std::runtime_error("Can't find animation" + animationNameInAnimator +" in animator \"" );

    const SBTSpriteAtlas& atlas = m_textures.get(m_currentAnimation->second.getMyAtlasFileName() );
    m_renderSprite.setTexture(atlas.getTexture() );

    m_currentTime = sf::Time::Zero;
    m_renderSprite.setTextureRect(m_currentAnimation->second.getFrame(0).getRect() );
}

void SBTAnimator2::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_renderSprite, states);
}

void SBTAnimator2::update(sf::Time dt)
{
    if(!m_animations.empty() )
    {
        m_currentTime += dt;
        auto animation = m_currentAnimation->second;
        int frame = static_cast<int>(m_currentTime.asSeconds() / animation.getDuration().asSeconds() * animation.size() );
        if(animation.isLooping() )
            frame %= animation.size();
        else
            frame = animation.size() - 1;
        m_renderSprite.setTextureRect(animation.getFrame(frame).getRect() );
    }
}

const sf::Sprite& SBTAnimator2::getRenderSprite() const
{
    return m_renderSprite;
}

sf::Vector2u SBTAnimator2::getSize()
{
    return {static_cast<unsigned>(m_renderSprite.getTextureRect().width), static_cast<unsigned>(m_renderSprite.getTextureRect().height) };
}

SBTAnimation* SBTAnimator2::findAnimation(const string& animationNameInAnimator)
{
    auto itr = m_animations.find(animationNameInAnimator);
    if(itr != m_animations.end() )
        return &itr->second;
    else
        throw std::runtime_error("Can't find animation" + animationNameInAnimator +" in animator \"" );
};

const SBTAnimation* SBTAnimator2::getCurrentAnimation()
{
    return (m_currentAnimation == m_animations.end())? nullptr : &(m_currentAnimation->second);
}