#include <iostream>
#include <SFML/Graphics.hpp>
#include "map.h"
#include "globals.h"
#include "player.h"
#include "SFML/Audio.hpp"


using namespace sf;

int main()
{
	Map drawing;
	//Player draw_p;
	Player z("hero_d.png", 48, 48, 23.0, 23.0);
	Map m;
	//Player z;
	Clock clock;
	Music music;
	music.openFromFile("audio/ost.ogg");
	music.setVolume(50);
	music.play();
	music.setLoop(true);
	

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		window.clear(Color(33, 30, 30));
		m.drawing();
		z.draw_p();

		window.draw(z.hpbar);

		window.display();
	}

	return 0;

}