#include "SBTAbstractApplicationState.h"
#include "SBTStateStack.h"

SBTAbstractApplicationState::~SBTAbstractApplicationState()
{
	
}

void SBTAbstractApplicationState::requestStackPush(int stateID, state_param_ptr param)
{
	mStack->pushState(stateID, move(param) );
}

void SBTAbstractApplicationState::requestStackPop()
{
	mStack->popState();
}

void SBTAbstractApplicationState::requestStateCLear()
{
	mStack->clearState();
}

SBTContext SBTAbstractApplicationState::getContext() const
{
	return mContext;
}

void SBTAbstractApplicationState::setBackGround(const sf::Texture* texture)
{
	mTexture = texture;
}

const sf::Texture* SBTAbstractApplicationState::getTexture()
{
	return mTexture;
}

void SBTAbstractApplicationState::renderBackGround(sf::RenderWindow& window)
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