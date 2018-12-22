#include "SFML/Graphics.hpp"
#include <iostream>
#include "map.h"
#include "globals.h"
#include "Enemy.h"



Entity::Entity()
{

}



Entity::Entity(String File, float X, float Y, int W, int H, String Name) {
	File;
	w = W; h = H;
	image.loadFromFile("images/" + File);
	texture.loadFromImage(image);

	sprite.setTexture(texture);
	x = X; y = Y;
	sprite.setTextureRect(IntRect(0, 0, w, h));
	sprite.setOrigin(w / 2, h / 2);

	x = X; y = Y; w = W; h = H; name = Name; 
	speed = 0; 
	moveTimer = 0;
	dy = 0;
	isMove = false;
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setOrigin(w / 2, h / 2);
};


police::police(String File, float X, float Y, int W, int H, String Name) {
	image.loadFromFile("police.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 32, 32));
	dy = 0.1;
	CurrentFrame = 0;
}


dogs::dogs(String File, float X, float Y, int W, int H, String Name) {
	image.loadFromFile("dogs.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 32, 32));
	dy = 0.1;
	CurrentFrame = 0;
}

void Entity::checkCollisionWithMap(float Dx, float Dy)//ф ция проверки столкновений с картой
{
	for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
		for (int j = x / 32; j < (x + w) / 32; j++)
		{
			if (TileMap[i][j] == '0')//если элемент наш тайлик земли, то
			{
				if (Dy > 0) { y = i * 32 - h; dy = -0.1; sprite.scale(-1, 1);
				}
			//по Y вниз=>идем в пол(стоим на месте) или падаем. В этот момент надо вытолкнуть персонажа и поставить его на землю, при этом говорим что мы на земле тем самым снова можем прыгать
				if (Dy < 0) { y = i * 32 + 32; dy = 0.1; sprite.scale(-1, 1);
				}//столкновение с верхними краями карты(может и не пригодиться)
				if (Dx > 0) { x = j * 32 - w;  }//с правым краем карты
				if (Dx < 0) { x = j * 32 + 32;  }// с левым краем карты
			}
		}
}

void Entity::update(float time)
{
	if (name == "police") {//для персонажа с таким именем логика будет такой

		moveTimer += time; if (moveTimer > 2500) { dy *= -1; moveTimer = 0; }//меняет направление примерно каждые 2/5 сек
		checkCollisionWithMap(dx, 0);//обрабатываем столкновение по y
		y += dy * time;
		sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра

	}

	if (name == "dog") {//для персонажа с таким именем логика будет такой

		moveTimer += time; if (moveTimer > 2500) { dy *= -1; moveTimer = 0; }//меняет направление примерно каждые 3 сек
		checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
		x += dy * time;
		sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
	}
	sprite.setPosition(x, y);
	checkCollisionWithMap(dx, dy);
}

void Entity::draw()
{
	time = clock.getElapsedTime().asMicroseconds();
	clock.restart();

	time = time / 800;

	//Player p("hero_d.png", 48, 48, 34.0, 34.0);//создаем объект p класса player,задаем "hero.png" как имя файла+расширение, далее координата Х,У, ширина, высота

	update(time);

	window.draw(sprite);

}


