#pragma once
#include <SFML\Graphics.hpp>


void centerOrigin(sf::Text& txt);

//void centerOrigin(sf::Text& txt)
//{
//	sf::FloatRect tmp = txt.getLocalBounds();
//	txt.setOrigin(std::floor(tmp.left + tmp.width / 2.f), std::floor(tmp.top + tmp.height / 2.f)) ;
//}