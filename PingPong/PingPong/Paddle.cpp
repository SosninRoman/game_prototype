#include "Paddle.h"


void Paddle::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const 
{
	target.draw(mRect, states);
}