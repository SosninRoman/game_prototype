#include <iostream>
#include <random>
#include <ctime>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Application.h"


int main(int argc, char* argv[])
{
	std::srand(time(NULL));
	Application app;
	app.run();
	return 0;
}