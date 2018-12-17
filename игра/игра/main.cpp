#include <iostream>
#include <SFML/Graphics.hpp>
#include "map.h"
#include "globals.h"
#include "player.h"


using namespace sf;

int main()
{
	Map drawing;
	//Player draw_p;
	Player z("hero_d.png", 48, 48, 23.0, 23.0);
	Map m;
	//Player z;
	Clock clock;
	

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		m.drawing();
		z.draw_p();


		window.display();
	}

	return 0;

}