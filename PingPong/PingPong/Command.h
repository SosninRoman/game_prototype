#pragma once

#include <functional>
#include <iostream>
#include <SFML/Graphics.hpp>

class SceneNode;

enum class RecieverType
{
	None = 0,
	Scene = 1,
	LeftPaddle = 1 << 1,
	RightPaddle = 1 << 2,
	Ball = 1 << 3,
};

struct Command
{
	Command():category(RecieverType::None){}
	std::function<void (SceneNode&, sf::Time)> action;
	RecieverType category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
	return [fn] (SceneNode& node, sf::Time dt)
	{
		auto& cast_node = dynamic_cast<GameObject&>(node);
		fn(cast_node, dt);
	};
}
