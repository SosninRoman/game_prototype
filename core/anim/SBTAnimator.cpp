//
// Created by G750 on 29.11.2017.
//

#include "SBTAnimator.h"
#include "SBTFrame.h"
#include "SBTSpriteAtlas.h"

SBTAnimator::SBTAnimator(GraphicResourceHolder* textures):
        m_graphicResources(textures), m_currentAnimation(m_animations.end())
{
}

void SBTAnimator::addAnimation(const std::string& GraphicResourceID, const string& sequenceIDInGraphicResource,
                  const animationID& animationNameInAnimator, sf::Time duration, bool looping)
{
    const SBTAbstractGraphicResource& resource = m_graphicResources->getByID(GraphicResourceID);
    const SBTSequence& seq = resource.getSequence(sequenceIDInGraphicResource);
    SBTAnimation anim(&seq, duration, looping);
    auto itr = m_animations.insert(make_pair(animationNameInAnimator, anim) );
    if(!itr.second)
        throw std::runtime_error("animation " + animationNameInAnimator +" already exist in animator \"" );
}

void SBTAnimator::switchAnimation(const string& animationNameInAnimator)
{
    m_currentAnimation = m_animations.find(animationNameInAnimator);
    if(m_currentAnimation == m_animations.end() )
        throw std::runtime_error("Can't find animation" + animationNameInAnimator +" in animator \"" );

    const SBTAbstractGraphicResource& atlas = m_graphicResources->getByFilename(m_currentAnimation->second.getMyResourceFileName() );
    m_renderSprite.setTexture(atlas.getTexture() );

    m_currentTime = sf::Time::Zero;
    m_renderSprite.setTextureRect(m_currentAnimation->second.getFrame(0).getRect() );
    //
    m_renderSprite.setRotation(m_currentAnimation->second.getAngle(0) );
}

void SBTAnimator::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_renderSprite, states);
}

void SBTAnimator::update(sf::Time dt)
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
        //
        m_renderSprite.setRotation(animation.getAngle(frame) );
    }
}

const sf::Sprite& SBTAnimator::getRenderSprite() const
{
    return m_renderSprite;
}

sf::Vector2u SBTAnimator::getSize()
{
    return {static_cast<unsigned>(m_renderSprite.getTextureRect().width), static_cast<unsigned>(m_renderSprite.getTextureRect().height) };
}

SBTAnimation* SBTAnimator::findAnimation(const string& animationNameInAnimator)
{
    auto itr = m_animations.find(animationNameInAnimator);
    if(itr != m_animations.end() )
        return &itr->second;
    else
        throw std::runtime_error("Can't find animation" + animationNameInAnimator +" in animator \"" );
};

const SBTAnimation* SBTAnimator::getCurrentAnimation()
{
    return (m_currentAnimation == m_animations.end())? nullptr : &(m_currentAnimation->second);
}