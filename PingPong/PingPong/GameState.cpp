#include "GameState.h"
#include <random>

bool isPlaying;


GameState::GameState(StateStack& stack, Context context):
	State(stack, context), pi(3.14159)
{
	//const float pi = 3.14159;
	ball_size = 10.f;
	sf::Vector2u gameWindowSize = getContext().window->getSize(); 
	sf::Vector2f paddle_size(25, 100);
	isPlaying = true;
	ball_velocity = gameWindowSize.x / 5;
	paddle_velocity = gameWindowSize.y / 50;

	sf::View gameView = getContext().window->getView();
	//Create ball
	ball.setRadius(ball_size);
	ball.setOutlineColor(sf::Color::Black);
	ball.setOutlineThickness(1);
	ball.setFillColor(sf::Color::White);
	ball.setOrigin(sf::Vector2f(ball_size / 2, ball_size / 2));
	ball.setPosition(gameView.getCenter().x, gameView.getCenter().y);
	ball_direction = rand() / static_cast<float>(RAND_MAX) * pi;
	//
	
	//Create right paddle
	right_puddle.setSize(paddle_size);
	right_puddle.setOrigin(paddle_size.x / 2, paddle_size.y / 2);
	right_puddle.setPosition(static_cast<float>(gameWindowSize.x - paddle_size.x/2), static_cast<float>(gameWindowSize.y / 2));
	right_puddle.setOutlineThickness(1);
	right_puddle.setOutlineColor(sf::Color::Black);
	right_puddle.setFillColor(sf::Color::Red);
	//
	
	//Create left paddle
	left_puddle.setSize(paddle_size);
	left_puddle.setOrigin(paddle_size.x / 2, paddle_size.y / 2);
	left_puddle.setPosition(static_cast<float>(paddle_size.x / 2), static_cast<float>(gameWindowSize.y / 2));
	left_puddle.setOutlineThickness(1);
	left_puddle.setOutlineColor(sf::Color::Black);
	left_puddle.setFillColor(sf::Color::Red);
}

void GameState::draw()
{
	sf::RenderWindow& window = *getContext().window; 
	window.draw(ball);
	window.draw(right_puddle);
	window.draw(left_puddle);
}

bool GameState::update(sf::Time dt)
{
	sf::Vector2u wSize = getContext().window->getSize();
	float factor = ball_velocity * dt.asSeconds();
	ball.move( std::cos(ball_direction) * factor, std::sin(ball_direction) * factor);
	if (ball.getGlobalBounds().intersects(left_puddle.getGlobalBounds())) ball_direction = pi + ball_direction + (std::rand() % 20) * pi / 180;
	if (ball.getGlobalBounds().intersects(right_puddle.getGlobalBounds())) ball_direction = pi - ball_direction + (std::rand() % 20) * pi / 180;
	if (ball.getPosition().x - ball_size < 0.f)
    {
		requestStateCLear();
		requestStackPush(Title);
    }
	if (ball.getPosition().x + ball_size > wSize.x)
    {
        requestStateCLear();
		requestStackPush(Title);
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
	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	sf::View gameView = getContext().window->getView();
	sf::Vector2u gameWindowSize = getContext().window->getSize();
	switch(event.type)
			{

			case sf::Event::EventType::Closed:         
				requestStateCLear();
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
			}
	return true;
}