#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

using namespace sf;

class Entity {
public:

	Entity();

	Entity(String File, float X, float Y, int W, int H, String Name);
	void checkCollisionWithMap(float Dx, float Dy);
	void update(float time);
	float dx, dy;
	float x, y;
	int w, h;
	float speed;
	Image image;
	float time;
	Texture texture;
	Sprite sprite;
	String name; 
	float CurrentFrame;
	bool isMove;
	float moveTimer;
	void draw();
	Clock clock;
};


class police : public Entity {
public:
	police(String File, float X, float Y, int W, int H, String Name);
	
};

class dogs : public Entity {
public:
	dogs(String File, float X, float Y, int W, int H, String Name);
	
};
   