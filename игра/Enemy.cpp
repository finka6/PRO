#include "SFML/Graphics.hpp" 
#include <iostream> 
#include "map.h" 
#include "globals.h" 
#include "Enemy.h" 
#include "player.h" 



police::police(int x, int y) {
	t.loadFromFile("images/police1.png");
	sprite.setTexture(t);
	sprite.setTextureRect(IntRect(0, 0, 23, 23));
	rect = FloatRect(x * 32, y * 32, 0, 0);
	dy = -0.1;
}


dogs::dogs(int x, int y)
{
	t.loadFromFile("images/dog.png");
	sprite.setTexture(t);
	sprite.setTextureRect(IntRect(0, 0, 23, 23));
	rect = FloatRect(x * 32, y * 32, 0, 0);
	dx = -0.05;
}




void Entity::checkCollisionWithMap()//ф ция проверки столкновений с картой 
{

	for (int i = (rect.top) / 32; i < (rect.top + 32) / 32; i++)
		for (int j = (rect.left) / 32; j < (rect.left + 32) / 32; j++)
		{
			if (TileMap[i][j] == '0')
			{
				if (dx > 0) { rect.left = j * 32 - 32; }
				if (dx < 0) { rect.left = j * 32 + 32; }
				dx = dx * -1;
				if (dy > 0) { rect.top = i * 32 - 32; }
				if (dy < 0) { rect.top = i * 32 + 32; }
				dy = dy * -1;
			}
		}
}


void Entity::drawing(float pX, float pY, Player & playerhp)
{
	time = clock.getElapsedTime().asMicroseconds();
	clock.restart();

	time = time / 800;


	sprite.setPosition(rect.left, rect.top);

	rect.left = rect.left + dx * time;
	rect.top = rect.top + dy * time;
	checkCollisionWithMap();

	CurrentFrame += 0.005 * time; // для анимации 
	if (CurrentFrame > 3) CurrentFrame -= 3;
	if (dx < 0) sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 0, 32, 32, 32));
	if (dx > 0) sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 0, 64, 32, 32));
	if (dy < 0) sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 64, 32, 32));
	if (dy > 0) sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 32, 32, -32, 32));


	//Player p("hero_d.png", 48, 48, 34.0, 34.0);//создаем объект p класса player,задаем "hero.png" как имя файла+расширение, далее координата Х,У, ширина, высота 


	window.draw(sprite);

	if ((pY >= (rect.top - 15)) && (pY <= (rect.top + 32 + 15)) && (pX >= (rect.left - 15) && (pX <= (rect.left + 32 + 15)))) {
		playerhp.Damage();
	}

}