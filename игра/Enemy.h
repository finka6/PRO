#pragma once 
#include "SFML/Graphics.hpp" 
#include <iostream> 
#include "player.h" 

using namespace sf;

class Entity {
public:

	FloatRect rect;
	void checkCollisionWithMap();
	void drawing(float pX, float pY, Player & playerhp);
	float dx, dy;
	float x, y;
	int w, h;
	float speed;
	Image image;
	float time;
	Texture t;
	Sprite sprite;
	Sprite* ptr_sprite;
	String name;
	float CurrentFrame;
	bool isMove;
	float moveTimer;
	Clock clock;
};


class police : public Entity {
public:

	police(int x, int y);

};

class dogs : public Entity {
public:
	dogs(int x, int y);

};