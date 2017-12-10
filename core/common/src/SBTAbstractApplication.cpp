//
// Created by G750 on 12.11.2017.
//

#include <SBTSpriteAtlas.h>
#include "SBTAbstractApplication.h"

const sf::Time TPF = sf::seconds(1.f/60.f);

SBTAbstractApplication::SBTAbstractApplication(SBTGameWindow* window, SBTAbstractCommandManager* manager, FontHolder* fonts,
                                               GraphicResourceHolder* grapRes):
m_window(window), m_commandManager(manager), m_fontHolder(fonts), m_graphicResourcesHolder(grapRes),
m_stateStack(new SBTStateStack( SBTContext(window, fonts, manager, grapRes ) ) )
{

}

void SBTAbstractApplication::run()
{
    sf::Clock clock;

    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while(m_window->isOpen())
    {
        m_window->setFramerateLimit(90);

        sf::Time dt = clock.restart();

        timeSinceLastUpdate += dt;

        while(timeSinceLastUpdate > TPF)
        {
            timeSinceLastUpdate -= TPF;

            handleInput();

            update(TPF);

            if(m_stateStack->isEmpty()) m_window->close();
        }

        draw();
    }
}

void SBTAbstractApplication::update(sf::Time dt)
{
    m_stateStack->update(dt);
}

void SBTAbstractApplication::draw()
{
    m_window->clear(sf::Color::White);
    m_stateStack->draw();
    m_window->display();
}

void SBTAbstractApplication::handleInput()
{
    sf::Event event;
    while(m_window->pollEvent(event))
    {
        m_stateStack->handleEvent(event);

        if(event.type == sf::Event::Closed)
            m_window->close();
    }
}

void SBTAbstractApplication::loadFont(GraphicResourceID id, const std::string& filepath)
{
    m_fontHolder->load(id, filepath);
}

void SBTAbstractApplication::pushState(int id, state_param_ptr param )
{
    m_stateStack->pushState(id, std::move(param) );
}