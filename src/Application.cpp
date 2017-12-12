#include "Application.h"
#include "TitleState.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "StateIDEnum.h"
#include "SBTTexture.h"

Application::Application():
    SBTAbstractApplication(new SBTGameWindow(640, 480, "PingPong", sf::Style::Default), new Player, new FontHolder,
                           new GraphicResourceHolder)
{
	registerStates();

    loadFont("MainMenuFont", "../res/sansation.ttf");

    SBTTileSheet* ball_sheet = getGraphicResourceHolder()->createResource<SBTTileSheet>("BallTexture");

    ball_sheet->loadTexture("../res/ball_sprites.png");
    ball_sheet->setColumsCount(2);
    ball_sheet->setTileCount(4);
    ball_sheet->setTileHeight(25);
    ball_sheet->setTileWidth(25);

    ball_sheet->addSequence("ball_animation");
    ball_sheet->addTileToSequence("ball_animation", 0);
    ball_sheet->addTileToSequence("ball_animation", 1);

    SBTTileSheet* paddle_sheet = getGraphicResourceHolder()->createResource<SBTTileSheet>("PaddleTexture");

    paddle_sheet->loadTexture("../res/paddle.png");
    paddle_sheet->setTileWidth(25);
    paddle_sheet->setTileHeight(128);
    paddle_sheet->setTileCount(1);
    paddle_sheet->setColumsCount(1);

    paddle_sheet->addSequence("paddle_animation");
    paddle_sheet->addTileToSequence("paddle_animation", 0);

    loadGraphicResource<SBTTileSheet>("CubeTexture", "../res/box.tsx");

    loadGraphicResource<SBTTileSheet>("ServiceTexture", "../res/ball.tsx");

    loadGraphicResource<SBTTexture>("MenuBackGround", "../res/menu_background.png");

    loadGraphicResource<SBTTexture>("TitleBackGround", "../res/title_background.jpg");

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