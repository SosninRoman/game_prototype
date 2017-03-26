#include "Application.h"
#include "TitleState.h"
#include "GameState.h"
#include "ManeMenuState.h"

const sf::Time TPF = sf::seconds(1.f/60.f);

Application::Application():
	mWindow(sf::VideoMode(640, 480), "PingPong", sf::Style::Default),
	mStateStack(Context(mWindow))
{
	registerStates();
	mStateStack.pushState(Title);
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
	mStateStack.registerState<TitleState>(Title);
	mStateStack.registerState<GameState>(Game);
	mStateStack.registerState<MainMenuState>(MainMenu);
}