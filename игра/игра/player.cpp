#pragma once
#include <SFML/Graphics.hpp>
#include "player.h"
#include "globals.h"
#include <iostream>
#include "map.h"
#include "view.h"


Player::Player()
{

}

Player::Player(String File, float X, float Y, float W, float H)
{
	view.reset(sf::FloatRect(0, 0, 1800, 900));
	File;
	w = W; h = H;
	imagee.loadFromFile("images/" + File);	
	texturee.loadFromImage(imagee);

	sprite.setTexture(texturee);
	x = X; y = Y;
	sprite.setTextureRect(IntRect(0, 0, w, h));  
	sprite.setOrigin(w / 2, h / 2);

	dx = 0;
	dy = 0;
	speed = 0;
	dir = 0;
	key = 0;
	hp = 3;
	life = true;
	hpbar.setFillColor(Color::Red);
	hpbar.setPosition(64.f, 10.f);
	hpbar.setSize(Vector2f((float)hp * 60.f, 20.f));

	

	CurrentFrame = 0;//хранит текущий кадр
	Clock clock;


}

void Player::update(float time)
{


	switch (dir)
	{
	case 0: dx = speed; dy = 0;   break;
	case 1: dx = -speed; dy = 0;   break;
	case 2: dx = 0; dy = speed;   break;
	case 3: dx = 0; dy = -speed;   break;
	}

	x += dx * time;
	y += dy * time;


	speed = 0;
	sprite.setPosition(x, y); 
	InteractionWithMap();
	hpbar.setSize(Vector2f((float)hp * 60.f, 20.f));
}



float Player::getplayercoordinateX() {	
	return x;
}
float Player::getplayercoordinateY() {	
	return y;
}


void Player::draw_p() {

	time = clock.getElapsedTime().asMicroseconds();
	clock.restart();

	time = time / 800;
	
	//Player p("hero_d.png", 48, 48, 34.0, 34.0);//создаем объект p класса player,задаем "hero.png" как имя файла+расширение, далее координата Х,У, ширина, высота

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
		dir = 0; speed = 0.1;
		CurrentFrame += 0.005*time;
		if (CurrentFrame > 3) CurrentFrame -= 3;
		sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 65, 32, 32)); 

	}

	if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
		dir = 3; speed = 0.1;
		CurrentFrame += 0.005*time;
		if (CurrentFrame > 3) CurrentFrame -= 3;
		sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 96, 32, 32)); 

	}

	if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) { 
		dir = 2; speed = 0.1;
		CurrentFrame += 0.005*time; 
		if (CurrentFrame > 3) CurrentFrame -= 3;
		sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 0, 32, 32));
	}

	update(time);

	window.draw(sprite);

	getplayercoordinateforview(coordinatePlayerX, coordinatePlayerY);	

	viewmap(time);

	window.setView(view);

}


void Player::InteractionWithMap()
{

	for (int i = y / 32; i < ((y + h) / 32); i++)
		for (int j = x / 32; j < ((x + w) / 32); j++)
		{
			if (TileMap[i][j] == '0')
			{
				if (dy > 0)
				{
					y = i * 32 - h;
				}
				if (dy < 0)
				{
					y = i * 32 + 32;
				}
				if (dx > 0)
				{
					x = j * 32 - w;
				}
				if (dx < 0)
				{
					x = j * 32 + 32;
				}

			}

			if (TileMap[i][j] == 'k') {
				TileMap[i][j] = ' ';
				key += 1;



			}
				if (TileMap[i][j] == 'c') 
				{
					if (dy > 0)
					{
						y = i * 32 - h;
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
					hp += 1;//если взяли сердечко,то переменная health=health+1;
					TileMap[i][j] = ' ';
				}
			
		}
}



