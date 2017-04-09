#include "ManeMenuState.h"
#include <assert.h>
#include "Utility.h"

MainMenuState::MainMenuState(StateStack& stack, Context context):
	State(stack, context)
{
	assert(mFont.loadFromFile("res/sansation.ttf"));
	sf::Text playText;
	playText.setFont(mFont);
	playText.setString("PLAYS");
	centerOrigin(playText);
	playText.setPosition(getContext().window->getSize().x / 2.f, getContext().window->getSize().y / 4.f);

	sf::Text exitText;
	exitText.setFont(mFont);
	exitText.setString("EXIT");
	centerOrigin(exitText);
	exitText.setPosition(getContext().window->getSize().x / 2.f, getContext().window->getSize().y / 4.f * 3.f);

	mOptions.push_back(playText);
	mOptions.push_back(exitText);

	mActiveOption = 0;
	setColorOfText();
}


bool MainMenuState::update(sf::Time dt)
{
	return false;
}

void MainMenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	for(auto text:mOptions)
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
				requestStackPush(ID::Game);
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
	{
		itr->setColor(sf::Color::Black);
	}
	mOptions[mActiveOption].setColor(sf::Color::Red);
}
