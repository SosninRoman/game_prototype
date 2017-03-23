#include <iostream>
#include <random>
#include <ctime>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Application.h"

int main_old(int argc, char* argv[])
{
	std::srand(time(NULL));
	const float pi = 3.14159; 
	//Options
	float ball_size = 10.f;
	sf::Vector2i gameWindowSize(600, 400); 
	sf::Vector2f paddle_size(25, 100);
	bool isPlaying = false;
	float ball_velocity = gameWindowSize.x / 5;
	float paddle_velocity = gameWindowSize.y / 50;

	//loading resourses
	sf::Font gameFont;
	if(!gameFont.loadFromFile("res/sansation.ttf")) return -1;
	
	//Create Window
	sf::Uint32 st2 = sf::Style::Titlebar | sf::Style::Close ;
	sf::Uint32 st_default = sf::Style::Default;
	sf::RenderWindow window(sf::VideoMode(gameWindowSize.x,gameWindowSize.y), "The title", st2);
	sf::Vector2u wSize = window.getSize();
	sf::String buf;
	sf::View gameView(sf::FloatRect(0, 0, wSize.x, wSize.y));
	sf::Vector2u wsz = window.getSize();

	//Create Text
	sf::Text gameText("START", gameFont);
	gameText.setColor(sf::Color::Black);
	gameText.setCharacterSize(20);
	sf::FloatRect textGRect = gameText.getGlobalBounds();
	sf::FloatRect textLRect = gameText.getLocalBounds();
	auto tmpor = sf::Vector2f(textLRect.width / 2.0f , textLRect.height / 2.0f);
	gameText.setOrigin(tmpor.x , tmpor.y);
	auto tmpr = sf::Vector2f(wSize.x / 2.0f , wSize.y / 2.0f);
	gameText.setPosition(tmpr);
	auto tmppos = gameText.getPosition();
	auto org = gameText.getOrigin();
	
	//Create ball
	sf::CircleShape ball;
	ball.setRadius(ball_size);
	ball.setOutlineColor(sf::Color::Black);
	ball.setOutlineThickness(1);
	ball.setFillColor(sf::Color::White);
	ball.setOrigin(sf::Vector2f(ball_size / 2, ball_size / 2));
	ball.setPosition(gameView.getCenter().x, gameView.getCenter().y);
	float ball_direction = rand() / static_cast<float>(RAND_MAX) * pi;
	//
	
	//Create right paddle
	sf::RectangleShape right_puddle;
	right_puddle.setSize(paddle_size);
	right_puddle.setOrigin(paddle_size.x / 2, paddle_size.y / 2);
	right_puddle.setPosition(static_cast<float>(gameWindowSize.x - paddle_size.x/2), static_cast<float>(gameWindowSize.y / 2));
	right_puddle.setOutlineThickness(1);
	right_puddle.setOutlineColor(sf::Color::Black);
	right_puddle.setFillColor(sf::Color::Red);
	//
	
	//Create left paddle
	sf::RectangleShape left_puddle;
	left_puddle.setSize(paddle_size);
	left_puddle.setOrigin(paddle_size.x / 2, paddle_size.y / 2);
	left_puddle.setPosition(static_cast<float>(paddle_size.x / 2), static_cast<float>(gameWindowSize.y / 2));
	left_puddle.setOutlineThickness(1);
	left_puddle.setOutlineColor(sf::Color::Black);
	left_puddle.setFillColor(sf::Color::Red);

	//Time
	sf::Clock gClock;
	sf::Time deltaTime;

	//Game loop
	while(window.isOpen())
	{
		deltaTime = gClock.restart();
		//Events heandling
		sf::Event event;
        while (window.pollEvent(event))
        {
			switch(event.type)
			{
			case sf::Event::TextEntered:
				buf += event.text.unicode;
				break;
			case sf::Event::EventType::Closed:         
					window.close();
					break;
			case sf::Event::EventType::KeyPressed:
				if(event.key.code == sf::Keyboard::Space)
				{
					if(!isPlaying) isPlaying = true;
					ball.setPosition(gameView.getCenter().x, gameView.getCenter().y);
					float ball_direction = rand() / static_cast<float>(RAND_MAX) * pi;
				}
				if(event.key.code == sf::Keyboard::S) 
				{
					if(left_puddle.getPosition().y + paddle_size.y / 2 < gameWindowSize.y)
					left_puddle.move(0,paddle_velocity);
				}
				if(event.key.code == sf::Keyboard::W)
				{
					if(left_puddle.getPosition().y - paddle_size.y / 2 > 0)
					left_puddle.move(0,-paddle_velocity);
				}
				if(event.key.code == sf::Keyboard::Up)
				{
					if(right_puddle.getPosition().y - paddle_size.y / 2 > 0)
					right_puddle.move(0,-paddle_velocity);
				}
				if(event.key.code == sf::Keyboard::Down)
				{
					auto pos = right_puddle.getPosition();
					if(right_puddle.getPosition().y + paddle_size.y / 2 < gameWindowSize.y)
					right_puddle.move(0,paddle_velocity);
				}
				if(event.key.code == sf::Keyboard::Space)
				{
					window.setTitle(buf);
					buf.clear();
				}
				break;
			}	
        }
		//Update Scene
		if(isPlaying)
		{
			float factor = ball_velocity * deltaTime.asSeconds();
			ball.move( std::cos(ball_direction) * factor, std::sin(ball_direction) * factor);
			if (ball.getGlobalBounds().intersects(left_puddle.getGlobalBounds())) ball_direction = pi + ball_direction + (std::rand() % 20) * pi / 180;
			if (ball.getGlobalBounds().intersects(right_puddle.getGlobalBounds())) ball_direction = pi - ball_direction + (std::rand() % 20) * pi / 180;
			if (ball.getPosition().x - ball_size < 0.f)
            {
                isPlaying = false;
                gameText.setString("You lost!\nPress space to restart or\nescape to exit");
            }
			if (ball.getPosition().x + ball_size > wSize.x)
            {
                isPlaying = false;
				gameText.setString("You won!\nPress space to restart or\nescape to exit");
            }
            if (ball.getPosition().y - ball_size < 0.f)
            {
				ball_direction = -ball_direction;
                ball.setPosition(ball.getPosition().x, ball_size + 0.1f);
            }
			if (ball.getPosition().y + ball_size > wSize.y)
            {
				ball_direction = -ball_direction;
                ball.setPosition(ball.getPosition().x, wSize.y - ball_size - 0.1f);
            }
		}
		//Render Cycle
		window.clear(sf::Color::Green);
		if(isPlaying)
		{
			window.draw(ball);
			window.draw(right_puddle);
			window.draw(left_puddle);
		}
		else
		{
			window.draw(gameText);
		}
		window.display();
	}
	//The end of game loop
	return 0;
}


int main(int argc, char* argv[])
{
	std::srand(time(NULL));
	Application app;
	app.run();
	return 0;
}