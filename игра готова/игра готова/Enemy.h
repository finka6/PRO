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
	float CurrentFrame;

	Clock clock;




};


class Police : public Entity {
public:

	Police(int x, int y);

};

class Dogs : public Entity {
public:

	Dogs(int x, int y);

};