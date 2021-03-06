#include "TitleState.h"
#include <assert.h>
#include "StateIDEnum.h"

TitleState::TitleState(SBTStateStack& stack, SBTContext context, state_param_ptr param):
		SBTAbstractApplicationState(stack, context, std::move(param) ),
	mTextEffectTime(sf::Time::Zero), 
	mShow(true)
{
	mText.setFont(getContext().fonts->getByID("MainMenuFont") );
	
	mText.setFillColor(sf::Color::Black);
	
	mText.setCharacterSize(20);
	
	mText.setString("PRESS TO START GAME");

	sf::FloatRect textLRect = mText.getLocalBounds();
	
	auto tmpor = sf::Vector2f( (textLRect.left + textLRect.width / 2.0f) ,std::floor(textLRect.top + textLRect.height / 2.0f) );
	
	mText.setOrigin(tmpor.x , tmpor.y);
	
	mText.setPosition(context.window->getView().getSize() / 2.f);

	setBackGround(&getContext().graphicResources->getByID("TitleBackGround").getTexture());
}

void TitleState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	
	renderBackGround(window);
	
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
		
		requestStackPush(StateID::MainMenu);
	}
	
	return true;
}
