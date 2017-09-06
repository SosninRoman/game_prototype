#include "PauseState.h"

void centerOrigin_local(sf::Text& txt);

PauseState::PauseState(StateStack& stack, Context context, state_param_ptr param):
	State(stack, context, std::move(param) )
{
	//assert(mFont.loadFromFile("res/sansation.ttf"));
	mFont = getContext().fonts->get(MainMenuFont);
	sf::Text playText;
	playText.setFont(mFont);
	playText.setString("RESUME");
	centerOrigin_local(playText);
	playText.setPosition(getContext().window->getSize().x / 2.f, getContext().window->getSize().y / 4.f);

	sf::Text exitText;
	exitText.setFont(mFont);
	exitText.setString("QUIT");
	centerOrigin_local(exitText);
	exitText.setPosition(getContext().window->getSize().x / 2.f, getContext().window->getSize().y / 4.f * 3.f);

	mOptions.push_back(playText);
	mOptions.push_back(exitText);

	mActiveOption = 0;
	setColorOfText();
}


PauseState::~PauseState()
{
}

void PauseState::setColorOfText()
{
	for(std::vector<sf::Text>::iterator itr = mOptions.begin(); itr != mOptions.end(); ++itr)
	{
		itr->setColor(sf::Color::Black);
	}
	mOptions[mActiveOption].setColor(sf::Color::Red);
}

bool PauseState::update(sf::Time dt)
{
	return false;
}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	for(auto text:mOptions)
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
				requestStackPush(ID::MainMenu);
			}
		}
	}
	return false;
}

void centerOrigin_local(sf::Text& txt)
{
	sf::FloatRect tmp = txt.getLocalBounds();
	txt.setOrigin(std::floor(tmp.left + tmp.width / 2.f), std::floor(tmp.top + tmp.height / 2.f)) ;
}