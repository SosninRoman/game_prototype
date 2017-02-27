#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main(int argc, char* argv[])
{
	//Options
	float ball_size = 10.f;
	float ball_velocity = 1.f;
	float paddle_velocity = 1.5;
	sf::Vector2i gameWindowSize(300, 200); 
	sf::Vector2f paddle_size(25, 100);
	int ball_direction = 1;
	//
	sf::Uint32 st2 = sf::Style::Titlebar | sf::Style::Close ;
	sf::Uint32 st_default = sf::Style::Default;
	sf::RenderWindow window(sf::VideoMode(gameWindowSize.x,gameWindowSize.y), "The title", st2);
	sf::String buf;
	//
	sf::Vector2u wsz = window.getSize();
	//Create ball
	sf::CircleShape ball;
	ball.setRadius(ball_size);
	ball.setOutlineColor(sf::Color::Black);
	ball.setOutlineThickness(1);
	ball.setFillColor(sf::Color::White);
	ball.setOrigin(sf::Vector2f(ball_size / 2, ball_size / 2));
	ball.setPosition(gameWindowSize.x / 2, gameWindowSize.y / 2);
	//
	//Create right paddle
	sf::RectangleShape right_puddle;
	right_puddle.setSize(paddle_size);
	right_puddle.setOrigin(paddle_size.x / 2, paddle_size.y / 2);
	right_puddle.setPosition(gameWindowSize.x - paddle_size.x/2, gameWindowSize.y / 2);
	right_puddle.setOutlineThickness(1);
	right_puddle.setOutlineColor(sf::Color::Black);
	right_puddle.setFillColor(sf::Color::Red);
	//
	//Create left paddle
	sf::RectangleShape left_puddle;
	left_puddle.setSize(paddle_size);
	left_puddle.setOrigin(paddle_size.x / 2, paddle_size.y / 2);
	left_puddle.setPosition(paddle_size.x/2, gameWindowSize.y / 2);
	left_puddle.setOutlineThickness(1);
	left_puddle.setOutlineColor(sf::Color::Black);
	left_puddle.setFillColor(sf::Color::Red);
	//
	while(window.isOpen())
	{
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
		ball.move(ball_velocity * ball_direction, 0);
		if (ball.getGlobalBounds().intersects(left_puddle.getGlobalBounds())) ball_direction = 1;
		if (ball.getGlobalBounds().intersects(right_puddle.getGlobalBounds())) ball_direction = -1;
		//Render Cycle
		window.clear(sf::Color::Green);
		window.draw(ball);
		window.draw(right_puddle);
		window.draw(left_puddle);
		window.display();
	}
	return 0;
}
