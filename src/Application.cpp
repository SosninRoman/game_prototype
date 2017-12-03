#include "Application.h"
#include "TitleState.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "StateIDEnum.h"
#include "ResourcesIDEnum.h"

//const sf::Time TPF = sf::seconds(1.f/60.f);

Application::Application():
    SBTAbstractApplication(new SBTGameWindow(640, 480, "PingPong", sf::Style::Default), new Player, new FontHolder,
                           new TextureHolder, new AtlasHolder, new TileSheetHolder)
{
	registerStates();

    loadFont(MainMenuFont, "../res/sansation.ttf");

    loadTexture(BackGroundTexture,"../res/back.jpg");

    loadTexture(BallTexture,"../res/ball_sprites.png");

    loadTexture(PaddleTexture,"../res/paddle.png");

    loadTexture(CubeTexture,"../res/box.tsx");

    loadTexture(ServiceTexture, "../res/ball.tsx");

    loadTexture(MenuBackGround, "../res/menu_background.png");

    loadTexture(TitleBackGround, "../res/title_background.jpg");

    pushState(StateID::Title);
}

void Application::registerStates()
{
    registerState<TitleState>(StateID::Title);
    registerState<GameState>(StateID::Game);
    registerState<MainMenuState>(StateID::MainMenu);
    registerState<PauseState>(StateID::Pause);
    registerState<GameOverState>(StateID::GameOver);
}