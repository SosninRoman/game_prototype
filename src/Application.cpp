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

    //loadTexture("BackGroundTexture", "../res/back.jpg");
    loadGraphicResource<SBTTexture>("BackGroundTexture", "../res/back.jpg");

    std::unique_ptr<SBTTileSheet> ball_sheet(new SBTTileSheet);
    ball_sheet->loadTexture("../res/ball_sprites.png");
    ball_sheet->setColumsCount(2);
    ball_sheet->setTileCount(4);
    ball_sheet->setTileHeight(25);
    ball_sheet->setTileWidth(25);

    ball_sheet->addSequence("ball_animation");
    ball_sheet->addTileToSequence("ball_animation", 0);

    //loadTexture(BallTexture,"../res/ball_sprites.png");
    addGraphicResource<SBTTileSheet>("BallTexture", std::move(ball_sheet) );

    //sf::Vector2i(0,0), sf::Vector2i(25,128)
    std::unique_ptr<SBTTileSheet> paddle_sheet(new SBTTileSheet);
    paddle_sheet->loadTexture("../res/paddle.png");
    paddle_sheet->setTileWidth(25);
    paddle_sheet->setTileHeight(128);
    paddle_sheet->setTileCount(1);
    paddle_sheet->setColumsCount(1);

    paddle_sheet->addSequence("paddle_animation");
    paddle_sheet->addTileToSequence("paddle_animation", 0);

    addGraphicResource("PaddleTexture", std::move(paddle_sheet) );
    //loadTexture(PaddleTexture,"../res/paddle.png");

    //loadTexture("CubeTexture", "../res/box.tsx");//Нужно добавить в Application загрузку ресурсов
    loadGraphicResource<SBTTexture>("CubeTexture", "../res/box.tsx");

    //loadTexture("ServiceTexture", "../res/ball.tsx");
    loadGraphicResource<SBTTexture>("ServiceTexture", "../res/ball.tsx");

    //loadTexture("MenuBackGround", "../res/menu_background.png");
    loadGraphicResource<SBTTexture>("MenuBackGround", "../res/menu_background.png");

    //loadTexture("TitleBackGround", "../res/title_background.jpg");
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