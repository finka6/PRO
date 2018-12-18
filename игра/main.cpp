#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
	Music music;
	music.openFromFile("audio/ost.ogg");
	music.setVolume(50);
	music.play();
	music.setLoop(true);



	while (window.isOpen() && z.hp>=0)
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		m.drawing();
		z.draw_p();

		window.draw(z.hpbar);
		window.display();
	}

	return 0;

}