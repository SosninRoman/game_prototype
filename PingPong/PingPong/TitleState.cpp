#include "TitleState.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <assert.h>

TitleState::TitleState(StateStack& stack, Context context):
	State(stack, context), mTextEffectTime(sf::Time::Zero), mShow(true)
{
	assert(mFont.loadFromFile("res/sansation.ttf"));

	mText.setFont(mFont);
	mText.setColor(sf::Color::Black);
	mText.setCharacterSize(20);
	mText.setString("PRESS TO START GAME");

	sf::FloatRect textLRect = mText.getLocalBounds();
	auto tmpor = sf::Vector2f( (textLRect.left + textLRect.width / 2.0f) ,std::floor(textLRect.top + textLRect.height / 2.0f) );
	mText.setOrigin(tmpor.x , tmpor.y);
	mText.setPosition(context.window->getView().getSize() / 2.f);
}

void TitleState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	if (mShow) 
		window.draw(mText);
}

bool TitleState::update(sf::Time dt)
{
	mTextEffectTime += dt;
	if(mTextEffectTime >= sf::seconds(0.5f))
	{
		mShow = !mShow;
		mTextEffectTime = sf::Time::Zero;
	}
	return true;
}

bool TitleState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		requestStackPop();
		requestStackPush(MainMenu);
	}
	return true;
}
