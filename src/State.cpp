#include "State.h"
#include "StateStack.h"

State::~State()
{
	
}

void State::requestStackPush(ID stateID, state_param_ptr param)
{
	mStack->pushState(stateID, move(param) );
}

void State::requestStackPop()
{
	mStack->popState();
}

void State::requestStateCLear()
{
	mStack->clearState();
}

Context State::getContext() const
{
	return mContext;
}

void State::setBackGround(sf::Texture* texture)
{
	mTexture = texture;
}

sf::Texture* State::getTexture()
{
	return mTexture;
}

void State::renderBackGround(sf::RenderWindow& window)
{
	sf::Vector2u sz = window.getSize();
	sf::Sprite background_sprite(*getTexture());
	sf::Vector2u sz_rend = getTexture()->getSize();
	sf::Vector2f scale(static_cast<float>(sz.x)/static_cast<float>(sz_rend.x), 
		static_cast<float>(sz.y) / static_cast<float>(sz_rend.y) );
	if(scale.x > 1)
		scale.x = 1;
	if(scale.y > 1)
		scale.y = 1;
	background_sprite.setScale(scale);
	window.draw(background_sprite);
}