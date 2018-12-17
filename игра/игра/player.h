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
	Player(String File, float X, float Y, float W, float H);
	int dir;
	Image imagee;
	Texture texturee;
	Sprite sprite;//сфмл спрайт
	void update(float time);
	void InteractionWithMap();
	float speed;
	Clock clock;
	float time;
	void draw_p();
	float CurrentFrame;
	float coordinatePlayerX, coordinatePlayerY;
	float getplayercoordinateY();
	float getplayercoordinateX();



};