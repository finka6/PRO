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

	File;//��� �����+����������
	w = W; h = H;//������ � ������
	imagee.loadFromFile("images/" + File);//���������� � image ���� ����������� ������ File �� ��������� ��, ��� �������� ��� �������� �������. � ����� ������ "hero.png" � ��������� ������ ���������� 	image.loadFromFile("images/hero/png");
	texturee.loadFromImage(imagee);//���������� ���� ����������� � ��������

	sprite.setTexture(texturee);//�������� ������ ���������
	x = X; y = Y;//���������� ��������� �������
	sprite.setTextureRect(IntRect(0, 0, w, h));  //������ ������� ���� ������������� 
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

	CurrentFrame = 0;//������ ������� ����
	Clock clock;


}

void Player::update(float time)
{


	switch (dir)//��������� ��������� � ����������� �� �����������. (������ ����� ������������� �����������)
	{
	case 0: dx = speed; dy = 0;   break;//�� ���� ������ ������������� ��������, �� ������ ��������. ��������, ��� �������� ���� ������ ������
	case 1: dx = -speed; dy = 0;   break;//�� ���� ������ ������������� ��������, �� ������ ��������. ����������, ��� �������� ���� ������ �����
	case 2: dx = 0; dy = speed;   break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ ����
	case 3: dx = 0; dy = -speed;   break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ �����
	}

	x += dx * time;
	y += dy * time;


	speed = 0;//�������� ��������, ����� �������� �����������.
	sprite.setPosition(x, y); //������� ������ � ������� x y , ����������. ���������� ������� � ���� �������, ����� �� ��� ������ ����� �� �����.
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
		dir = 0; speed = 0.1;//����������� ������, �� ����
		CurrentFrame += 0.005*time;
		if (CurrentFrame > 3) CurrentFrame -= 3;
		sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 65, 32, 32)); //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)

	}

	if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
		dir = 3; speed = 0.1;//����������� ����, �� ����
		CurrentFrame += 0.005*time;
		if (CurrentFrame > 3) CurrentFrame -= 3;
		sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 96, 32, 32)); //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)

	}

	if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) { //���� ������ ������� ������� ����� ��� ���� ����� 
		dir = 2; speed = 0.1;//����������� �����, �� ����
		CurrentFrame += 0.005*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
		if (CurrentFrame > 3) CurrentFrame -= 3;
		sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 0, 32, 32));


	}
	update(time);

	window.draw(sprite);//������ ���������� �� �����

}



void Player::InteractionWithMap()
{

	for (int i = y / 32; i < ((y + h) / 32); i++)//���������� �� ��������, �������������� � �������,, �� ���� �� ���� ����������� ������� 32*32, ������� �� ���������� � 9 �����. ��� ������� ������� ����.
		for (int j = x / 32; j < ((x + w) / 32); j++)//��� ����� �� 32, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
		{


			if (TileMap[i][j] == '0')//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
			{
				if (dy > 0)//���� �� ��� ����,
				{
					y = i * 32 - h;//�� �������� ���������� ����� ���������. ������� �������� ���������� ������ ���������� �� �����(�����) � ����� �������� �� ������ ������� ���������.
				}
				if (dy < 0)
				{
					y = i * 32 + 32;//���������� � ������� �����. dy<0, ������ �� ���� ����� (���������� ���������� ������)
				}
				if (dx > 0)
				{
					x = j * 32 - w;//���� ���� ������, �� ���������� � ����� ����� (������ 0) ����� ������ ���������
				}
				if (dx < 0)
				{
					x = j * 32 + 32;//���������� ���� �����
				}
			}
			if (TileMap[i][j] == 'k') {
				TileMap[i][j] = ' ';
				key += 1;



			}
			if (TileMap[i][j] == 'c') //���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
			{
				if (dy > 0)//���� �� ��� ����,
				{
					y = i * 32 - h;//�� �������� ���������� ����� ���������. ������� �������� ���������� ������ ���������� �� �����(�����) � ����� �������� �� ������ ������� ���������.
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
				hp += 80;//���� ����� ��������,�� ���������� health=health+1;
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


float Player::getplayercoordinateX() {	//���� ������� ����� �������� ���������� �	
	return x;
}
float Player::getplayercoordinateY() {	//���� ������� ����� �������� ���������� Y 	
	return y;
}

void Player::Damage() {

	hp--;
	return;
}