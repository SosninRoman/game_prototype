#include "Application.h"
#include "TitleState.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "PauseState.h"
#include "GameOverState.h"

const sf::Time TPF = sf::seconds(1.f/60.f);

Application::Application():
	mWindow(sf::VideoMode(640, 480), "PingPong", sf::Style::Default),
	mStateStack(Context(mWindow, mFontHolder, mPlayer, mTextureHolder))
{
	registerStates();
	mStateStack.pushState(ID::Title);

	mFontHolder.load(MainMenuFont, "res/sansation.ttf");
	mTextureHolder.load(BackGroundTexture,"res/back.jpg");
	mTextureHolder.load(BallTexture,"res/ball_sprites.png");
	mTextureHolder.load(PaddleTexture,"res/paddle.png");
	mTextureHolder.load(CubeTexture,"res/box.tsx");
	mTextureHolder.load(ServiceTexture, "res/ball.tsx");
	mTextureHolder.load(MenuBackGround, "res/menu_background.png");
	mTextureHolder.load(TitleBackGround, "res/title_background.jpg");
}


void Application::update(sf::Time dt)
{
	mStateStack.update(dt);
}

void Application::draw()
{
	mWindow.clear(sf::Color::White);
	mStateStack.draw();
	mWindow.display();
}

void Application::handleInput()
{
	sf::Event event;
	while(mWindow.pollEvent(event))
	{
		mStateStack.handleEvent(event);

		if(event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while(mWindow.isOpen())
	{
		mWindow.setFramerateLimit(90);
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while(timeSinceLastUpdate > TPF)
		{
			timeSinceLastUpdate -= TPF;
			handleInput();
			update(TPF);
			if(mStateStack.isEmpty()) mWindow.close();
		}
		draw();
	}
}

void Application::registerStates()
{
	mStateStack.registerState<TitleState>(ID::Title);
	mStateStack.registerState<GameState>(ID::Game);
	mStateStack.registerState<MainMenuState>(ID::MainMenu);
	mStateStack.registerState<PauseState>(ID::Pause);
	mStateStack.registerState<GameOverState>(ID::GameOver);
}