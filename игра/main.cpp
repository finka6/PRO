#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "map.h"
#include "globals.h"
#include "player.h"
#include "Enemy.h"
#include <list>


using namespace std;
using namespace sf;
void menu(RenderWindow & window) {
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("images/111.png");
	menuTexture2.loadFromFile("images/222.png");
	menuTexture3.loadFromFile("images/333.png");
	aboutTexture.loadFromFile("images/about.png");
	menuBackground.loadFromFile("images/back.jpg");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(50, 30);
	menu2.setPosition(50, 130);
	menu3.setPosition(50, 230);
	menuBg.setPosition(0, 0);
	Music prison;
	prison.openFromFile("audio/prison.ogg");
	prison.setVolume(70);
	prison.play();
	prison.setLoop(true);
	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));
		
		if (IntRect(50, 30, 350, 100).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Yellow); menuNum = 1; }
		if (IntRect(50, 130, 350, 100).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Yellow); menuNum = 2; }
		if (IntRect(50, 230, 350, 100).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Yellow); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) { window.draw(about); window.display(); while (!Mouse::isButtonPressed(Mouse::Right)); }
			if (menuNum == 3) { window.close(); isMenu = false; }

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
	////////////////////////////////////////////////////
}


void winner(RenderWindow & window)
{
	Texture winning_screen;
	winning_screen.loadFromFile("images/pobeg.jpg");
	Sprite winscreen(winning_screen);
	winscreen.setPosition(0, 0);

	window.draw(winscreen);
	window.display();
}
void ss(RenderWindow & window)
{
	Texture ricka;
	ricka.loadFromFile("images/rick.jpg");
	Sprite rick(ricka);
	rick.setPosition(0, 0);

	window.draw(rick);
	window.display();
}
void lose(RenderWindow & window)
{
	Texture losee;
	losee.loadFromFile("images/porazh.jpg");
	Sprite lose(losee);
	lose.setPosition(0, 0);

	window.draw(lose);
	window.display();
}


	
int main()
{

	menu(window);//вызов меню
	Map drawing;
	//Player draw_p;
	Player z("hero_d.png", 48, 48, 23.0, 23.0);
	Map m;
	//Player z;
	Clock clock;
	
	//////////////////////////////////////////////////СПИСОК//////////////////////////////////////////////////////////////////////


	std::list<Entity*> enemys;
	std::list<Entity*>::iterator bb;

	for (int i = 0; i < HEIGHT_MAP; i++) {
		for (int j = 0; j < WIDTH_MAP; j++) {

			if (TileMap[i][j] == 'L') {

				enemys.push_back(new police(j, i));
				cout << i << "   " << j << endl;

			}

			if (TileMap[i][j] == 'S') {

				enemys.push_back(new dogs(j, i));

			}

		}
	}

	
	Music music;
	music.openFromFile("audio/ost.ogg");
	music.setVolume(50);
	music.play();
	music.setLoop(true);

	

	
	Font font;//шрифт 
	font.loadFromFile("Ben_Krush.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text.setStyle(sf::Text::Bold);

		while (window.isOpen())
		{
			if (z.win >= 1)
			{
				music.stop();
				Music pobeda;
				pobeda.openFromFile("audio/pobeda.ogg");
				pobeda.setVolume(100);
				pobeda.play();
				window.close();
				RenderWindow window(sf::VideoMode(1400, 700), "GAME");
				winner(window); while (!Mouse::isButtonPressed(Mouse::Right));
			}
			if (z.hp <= 0)
			{
				music.stop();
				Music lost;
				lost.openFromFile("audio/lose.ogg");
				lost.setVolume(100);
				lost.play();
				window.close();
				RenderWindow window(sf::VideoMode(1400, 700), "GAME");
				lose(window); while (!Mouse::isButtonPressed(Mouse::Right));
			}
			if (z.ss >= 1)
			{
				music.stop();
				Music rick;
				rick.openFromFile("audio/ss.ogg");
				rick.setVolume(100);
				rick.play();
				window.close();
				RenderWindow window(sf::VideoMode(1300, 700), "GAME");
				ss(window); while (!Keyboard::isKeyPressed(Keyboard::Escape));
			}

		sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			window.clear(Color(33, 30, 30));
			m.drawing();
			z.draw_p();
			for (bb = enemys.begin(); bb != enemys.end(); bb++) {
				(*bb)->drawing(z.getplayercoordinateX(), z.getplayercoordinateY(), z);
			}

			text.setString("Здоровье:");
			text.setPosition(0,0);
			window.draw(text);
			window.draw(z.hpbar);
			window.display();
		
		}

	return 0;
}
		
	
	

