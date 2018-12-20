#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "player.h"
#include "globals.h"
#include <iostream>
#include "map.h"
using namespace sf;




Player::Player()
{

}

Player::Player(String File, float X, float Y, float W, float H)
{

	File;//имя файла+расширение
	w = W; h = H;//высота и ширина
	imagee.loadFromFile("images/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
	texturee.loadFromImage(imagee);//закидываем наше изображение в текстуру

	sprite.setTexture(texturee);//заливаем спрайт текстурой
	x = X; y = Y;//координата появления спрайта
	sprite.setTextureRect(IntRect(0, 0, w, h));  //Задаем спрайту один прямоугольник 
	sprite.setOrigin(w / 2, h / 2);

	dx = 0;
	dy = 0;
	speed = 0;
	dir = 0;
	key = 0;
	hp = 200;
	life = true;
	win = 0;
	hpbar.setFillColor(Color::Red);
	hpbar.setPosition(128, 10.f);
	hpbar.setSize(Vector2f((float)hp * 1.f, 10.f));
	ss = 0;

	CurrentFrame = 0;//хранит текущий кадр
	Clock clock;


}

void Player::update(float time)
{


	switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
	{
	case 0: dx = speed; dy = 0;   break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
	case 1: dx = -speed; dy = 0;   break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
	case 2: dx = 0; dy = speed;   break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
	case 3: dx = 0; dy = -speed;   break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
	}

	x += dx * time;
	y += dy * time;


	speed = 0;//зануляем скорость, чтобы персонаж остановился.
	sprite.setPosition(x, y); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
	InteractionWithMap();
	hpbar.setSize(Vector2f((float)hp * 1.f, 10.f));
}



void Player::draw_p() {
	time = clock.getElapsedTime().asMicroseconds();
	clock.restart();

	time = time / 650;


	//Player p("hero_d.png", 48, 48, 34.0, 34.0);

	float coordinatePlayerX, coordinatePlayerY = 0;
	coordinatePlayerX = getplayercoordinateX();
	coordinatePlayerY = getplayercoordinateY();



	if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
		dir = 1; speed = 0.1;
		CurrentFrame += 0.005*time;
		if (CurrentFrame > 3) CurrentFrame -= 3;
		sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 32, 32, 32));

	}


	if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
		dir = 0; speed = 0.1;//направление вправо, см выше
		CurrentFrame += 0.005*time;
		if (CurrentFrame > 3) CurrentFrame -= 3;
		sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 65, 32, 32)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)

	}

	if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
		dir = 3; speed = 0.1;//направление вниз, см выше
		CurrentFrame += 0.005*time;
		if (CurrentFrame > 3) CurrentFrame -= 3;
		sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 96, 32, 32)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)

	}

	if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) { //если нажата клавиша стрелка влево или англ буква 
		dir = 2; speed = 0.1;//направление вверх, см выше
		CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
		if (CurrentFrame > 3) CurrentFrame -= 3;
		sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 0, 32, 32));


	}
	update(time);

	window.draw(sprite);//рисуем квадратики на экран

}



void Player::InteractionWithMap()
{

	for (int i = y / 32; i < ((y + h) / 32); i++)//проходимся по тайликам, контактирующим с игроком,, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
		for (int j = x / 32; j < ((x + w) / 32); j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
		{


			if (TileMap[i][j] == '0')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
			{
				if (dy > 0)//если мы шли вниз,
				{
					y = i * 32 - h;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
				}
				if (dy < 0)
				{
					y = i * 32 + 32;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
				}
				if (dx > 0)
				{
					x = j * 32 - w;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
				}
				if (dx < 0)
				{
					x = j * 32 + 32;//аналогично идем влево
				}
			}
			if (TileMap[i][j] == 'k') {
				TileMap[i][j] = ' ';
				key += 1;



			}
			if (TileMap[i][j] == 'c') //если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
			{
				if (dy > 0)//если мы шли вниз,
				{
					y = i * 32 - h;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
				}

			}
			if (TileMap[i][j] == 'x')
			{
				if (key >= 1)
				{
					TileMap[i + 1][j] = '[';

				}
			}
			if (TileMap[i][j] == 'h')
			{
				hp += 80;//если взяли сердечко,то переменная health=health+1;
				TileMap[i][j] = ' ';

			}
			if (TileMap[i][j] == '1')
			{
				win += 1;
			}
			if (TileMap[i][j] == 's')
			{
				ss += 1;
			}

		}
}


float Player::getplayercoordinateX() {	//этим методом будем забирать координату Х	
	return x;
}
float Player::getplayercoordinateY() {	//этим методом будем забирать координату Y 	
	return y;
}

void Player::Damage() {

	hp--;
	return;
}