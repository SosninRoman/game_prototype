#include "SBTGameWindow.h"


SBTGameWindow::SBTGameWindow(int sz_x, int sz_y, const sf::String& title, sf::Uint32 style, const sf::ContextSettings& settings):
	RenderWindow(sf::VideoMode(sz_x, sz_y), title, style, settings),
	resolution(sz_x, sz_y)
{
}


SBTGameWindow::~SBTGameWindow()
{
}
