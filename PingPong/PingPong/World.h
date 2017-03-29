#pragma once
#include <array>
#include <SFML\Graphics.hpp>
#include "SceneNode.h"

class World: public sf::NonCopyable
{
public:
	enum Layer
	{
		BackGround,
		Ground,
		LayerCount
	};
	World(sf::RenderWindow& window);
	void draw();
	void update(sf::Time dt);
private:
	std::array<SceneNode::Ptr, LayerCount> mSceneLayers;
	sf::RenderWindow& mWindow;
	sf::FloatRect mWorldBounds;

	void buildScene();

	float ball_direction;
	float ball_size;
	const float pi;
	float ball_velocity;
	float paddle_velocity;
	sf::Vector2f paddle_size;
	sf::CircleShape ball;
	sf::RectangleShape right_puddle, left_puddle;
};

