#pragma once
#include <SFML/Graphics.hpp>

class winning_screen
{
public:
	void init(sf::RenderWindow* window);

private:
	sf::Font fontw;
	sf::Text winner;
};