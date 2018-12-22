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

void Entity::checkCollisionWithMap(float Dx, float Dy)//� ��� �������� ������������ � ������
{
	for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������� �����
		for (int j = x / 32; j < (x + w) / 32; j++)
		{
			if (TileMap[i][j] == '0')//���� ������� ��� ������ �����, ��
			{
				if (Dy > 0) { y = i * 32 - h; dy = -0.1; sprite.scale(-1, 1);
				}
			//�� Y ����=>���� � ���(����� �� �����) ��� ������. � ���� ������ ���� ���������� ��������� � ��������� ��� �� �����, ��� ���� ������� ��� �� �� ����� ��� ����� ����� ����� �������
				if (Dy < 0) { y = i * 32 + 32; dy = 0.1; sprite.scale(-1, 1);
				}//������������ � �������� ������ �����(����� � �� �����������)
				if (Dx > 0) { x = j * 32 - w;  }//� ������ ����� �����
				if (Dx < 0) { x = j * 32 + 32;  }// � ����� ����� �����
			}
		}
}

void Entity::update(float time)
{
	if (name == "police") {//��� ��������� � ����� ������ ������ ����� �����

		moveTimer += time; if (moveTimer > 2500) { dy *= -1; moveTimer = 0; }//������ ����������� �������� ������ 2/5 ���
		checkCollisionWithMap(dx, 0);//������������ ������������ �� y
		y += dy * time;
		sprite.setPosition(x + w / 2, y + h / 2); //������ ������� ������� � ����� ��� ������

	}

	if (name == "dog") {//��� ��������� � ����� ������ ������ ����� �����

		moveTimer += time; if (moveTimer > 2500) { dy *= -1; moveTimer = 0; }//������ ����������� �������� ������ 3 ���
		checkCollisionWithMap(dx, 0);//������������ ������������ �� �
		x += dy * time;
		sprite.setPosition(x + w / 2, y + h / 2); //������ ������� ������� � ����� ��� ������
	}
	sprite.setPosition(x, y);
	checkCollisionWithMap(dx, dy);
}

void Entity::draw()
{
	time = clock.getElapsedTime().asMicroseconds();
	clock.restart();

	time = time / 800;

	//Player p("hero_d.png", 48, 48, 34.0, 34.0);//������� ������ p ������ player,������ "hero.png" ��� ��� �����+����������, ����� ���������� �,�, ������, ������

	update(time);

	window.draw(sprite);

}


