#include "GameOverState.h"
#include "SBTUtility.h"
#include "GameOverStateParam.h"
#include "StateIDEnum.h"

GameOverState::GameOverState(SBTStateStack& stack, SBTContext context, state_param_ptr param):
		SBTAbstractApplicationState(stack, context, move(param) )
{
	mFont = getContext().fonts->getByID("MainMenuFont");
	
	sf::Text playText;
	
	playText.setFont(mFont);
	
	playText.setString("RESTART");
	
	centerOrigin(playText);
	
	playText.setPosition(getContext().window->getResolution().x / 2.f, getContext().window->getResolution().y / 4.f * 2.f);

	sf::Text exitText;
	
	exitText.setFont(mFont);
	
	exitText.setString("QUIT");
	
	centerOrigin(exitText);
	
	exitText.setPosition(getContext().window->getResolution().x / 2.f, getContext().window->getResolution().y / 4.f * 3.f);

	sf::Text congratText;
	
	congratText.setFont(mFont);
	
	GameOverParam* param_of_the_state = dynamic_cast<GameOverParam*>(mStateParam.get());
	
	if (param_of_the_state->mWinnerType == RecieverType::LeftPaddleRecieverType)
		congratText.setString("LEFT PLAYER WIN!");
	else
		congratText.setString("RIGHT PLAYER WIN!");
	
	centerOrigin(congratText);
	
	congratText.setPosition(getContext().window->getResolution().x / 2.f, getContext().window->getResolution().y / 4.f );
	
	congratText.setFillColor(sf::Color::Black);

	mOptions.push_back(playText);
	
	mOptions.push_back(exitText);
	
	mTextBox.push_back(congratText);

	mActiveOption = 0;
	
	setColorOfText();
}

GameOverState::~GameOverState()
{
}

void GameOverState::setColorOfText()
{
	for(std::vector<sf::Text>::iterator itr = mOptions.begin(); itr != mOptions.end(); ++itr)
	{
		itr->setFillColor(sf::Color::Black);
	}
	mOptions[mActiveOption].setFillColor(sf::Color::Red);
}

bool GameOverState::update(sf::Time dt)
{
	return false;
}

void GameOverState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	for(auto text : mOptions)
		window.draw(text);

	for(auto text : mTextBox)
		window.draw(text);
}

bool GameOverState::handleEvent(const sf::Event& event)
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
			if( mActiveOption == Restart)
			{
				requestStateCLear();
				requestStackPush(StateID::Game);
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