#include "MainMenuState.h"
#include "SBTUtility.h"
#include "StateIDEnum.h"
#include "ResourcesIDEnum.h"

MainMenuState::MainMenuState(SBTStateStack& stack, SBTContext context, state_param_ptr param):
		SBTAbstractApplicationState(stack, context, move(param) )
{
	mFont = getContext().fonts->getByID("MainMenuFont");
	
	sf::Text playText;
	
	playText.setFont(mFont);
	
	playText.setString("PLAY");
	
	centerOrigin(playText);

	playText.setPosition(getContext().window->getResolution().x / 2.f, getContext().window->getResolution().y / 4.f);

	sf::Text exitText;
	
	exitText.setFont(mFont);
	
	exitText.setString("EXIT");
	
	centerOrigin(exitText);
	
	exitText.setPosition(getContext().window->getResolution().x / 2.f, getContext().window->getResolution().y / 4.f * 3.f);

	mOptions.push_back(playText);
	
	mOptions.push_back(exitText);

	mActiveOption = 0;
	
	setColorOfText();

	//setBackGround(&getContext().textures->get(MenuBackGround).getTexture());

	setBackGround(&getContext().graphicResources->getByID("MenuBackGround").getTexture());
}


bool MainMenuState::update(sf::Time dt)
{
	return false;
}

void MainMenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	renderBackGround(window);

	for(const auto& text:mOptions)
		window.draw(text);
}

bool MainMenuState::handleEvent(const sf::Event& event)
{
	if( event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Up)
		{
			if((--mActiveOption) < 0) mActiveOption = mOptions.size()-1;
			
			setColorOfText();			
		}
		if (event.key.code == sf::Keyboard::Down)
		{
			mActiveOption = (mActiveOption + 1) % mOptions.size();
			
			setColorOfText();
		}
		if (event.key.code == sf::Keyboard::Return)
		{
			if( mActiveOption == Play)
			{
				requestStackPop();
				
				requestStackPush(StateID::Game);
			}
			if(mActiveOption == Exit)
			{
				requestStateCLear();
			}
		}
	}
	return false;
}

void MainMenuState::setColorOfText()
{
	for(std::vector<sf::Text>::iterator itr = mOptions.begin(); itr != mOptions.end(); ++itr)
		itr->setFillColor(sf::Color::White);
	
	mOptions[mActiveOption].setFillColor(sf::Color::Red);
}
