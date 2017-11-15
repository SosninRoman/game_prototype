#pragma once

#include <functional>
#include <iostream>
#include <SFML/Graphics.hpp>

class SBTAbstractSceneNode;

struct SBTCommand
{
    SBTCommand():category(0)
	{

	}
	std::function<void (SBTAbstractSceneNode&, sf::Time)> action;
	int category;
};

template <typename GameObject, typename Function>
std::function<void(SBTAbstractSceneNode&, sf::Time)> derivedAction(Function fn)
{
	return [fn] (SBTAbstractSceneNode& node, sf::Time dt)
	{
		auto& cast_node = dynamic_cast<GameObject&>(node);
		fn(cast_node, dt);
	};
}
