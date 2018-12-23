#pragma once
#include "globals.h" // теперь всё работает
#include <SFML/Graphics.hpp>
using namespace sf;



class Player {
private:
	float x, y;

public:
	float w, h, dx, dy;
	Player();
	~Player();
	Player(String File, float X, float Y, float W, float H);
	int dir;
	Image imagee;
	Texture texturee;
	Sprite sprite;
	void update(float time);
	void InteractionWithMap();
	float speed;
	Clock clock;
	float time;
	int key;
	int hp;
	void draw_p();
	float CurrentFrame;
	float coordinatePlayerX, coordinatePlayerY;
	float GetPlayerCoordinateY();
	void Damage();
	void bDamage();
	float GetPlayerCoordinateX();
	RectangleShape hpbar;
	int win;

};