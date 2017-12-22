#include "PauseState.h"
#include "SBTUtility.h"
#include "StateIDEnum.h"

PauseState::PauseState(SBTStateStack& stack, SBTContext context, state_param_ptr param):
	SBTAbstractApplicationState(stack, context, std::move(param) )
{
	mFont = getContext().fonts->getByID("MainMenuFont");
	
	sf::Text playText;
	
	playText.setFont(mFont);
	
	playText.setString("RESUME");
	
	centerOrigin(playText);
	
	playText.setPosition(getContext().window->getSize().x / 2.f, getContext().window->getSize().y / 4.f);

	sf::Text exitText;
	
	exitText.setFont(mFont);
	
	exitText.setString("QUIT");
	
	centerOrigin(exitText);
	
	exitText.setPosition(getContext().window->getSize().x / 2.f, getContext().window->getSize().y / 4.f * 3.f);

	mOptions.push_back(playText);
	
	mOptions.push_back(exitText);

	mActiveOption = 0;
	
	setColorOfText();
}

void PauseState::setColorOfText()
{
	for(std::vector<sf::Text>::iterator itr = mOptions.begin(); itr != mOptions.end(); ++itr)
	{
		itr->setFillColor(sf::Color::Black);
	}
	
	mOptions[mActiveOption].setFillColor(sf::Color::Red);
}

bool PauseState::update(sf::Time dt)
{
	return false;
}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	
	for(const auto& text : mOptions)
		window.draw(text);
}

bool PauseState::handleEvent(const sf::Event& event)
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
			if( mActiveOption == BackToPlay)
			{
				requestStackPop();
			}
			
			if(mActiveOption == ExitToMenu)
			{
				requestStateCLear();
				
				requestStackPush(StateID::MainMenu);
			}
		}
	}
	return false;
}