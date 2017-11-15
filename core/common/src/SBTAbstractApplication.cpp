//
// Created by G750 on 12.11.2017.
//

#include "SBTAbstractApplication.h"

const sf::Time TPF = sf::seconds(1.f/60.f);

SBTAbstractApplication::SBTAbstractApplication(SBTGameWindow* window, SBTAbstractCommandManager* manager, FontHolder* fonts, TextureHolder* txtrs):
mWindow(window), mCommandManager(manager), mFontHolder(fonts), mTextureHolder(txtrs),
mStateStack(new SBTStateStack( SBTContext(window, fonts, manager, txtrs ) ) )
{

}

SBTAbstractApplication::~SBTAbstractApplication()
{

}

void SBTAbstractApplication::run()
{
    sf::Clock clock;

    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while(mWindow->isOpen())
    {
        mWindow->setFramerateLimit(90);

        sf::Time dt = clock.restart();

        timeSinceLastUpdate += dt;

        while(timeSinceLastUpdate > TPF)
        {
            timeSinceLastUpdate -= TPF;

            handleInput();

            update(TPF);

            if(mStateStack->isEmpty()) mWindow->close();
        }

        draw();
    }
}

void SBTAbstractApplication::update(sf::Time dt)
{
    mStateStack->update(dt);
}

void SBTAbstractApplication::draw()
{
    mWindow->clear(sf::Color::White);
    mStateStack->draw();
    mWindow->display();
}

void SBTAbstractApplication::handleInput()
{
    sf::Event event;
    while(mWindow->pollEvent(event))
    {
        mStateStack->handleEvent(event);

        if(event.type == sf::Event::Closed)
            mWindow->close();
    }
}

void SBTAbstractApplication::loadTexture(int id, const std::string& filepath)
{
    mTextureHolder->load(id, filepath);
}

void SBTAbstractApplication::loadFont(int id, const std::string& filepath)
{
    mFontHolder->load(id, filepath);
}

void SBTAbstractApplication::pushState(int id, state_param_ptr param )
{
    mStateStack->pushState(id, std::move(param) );
}