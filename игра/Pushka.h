#pragma once
#include "SFML/Graphics.hpp" 
#include <iostream> 
#include "player.h" 

using namespace sf;

class Push {
public:

	FloatRect rect;
	void drawing();
	FloatRect polozenie();
	float uskorenie();

	void drawing(float pX, float pY, Player & playerhp);
	float dx, dy;
	float x, y;
	int w, h;
	float speed;
	Image image;
	float time;
	Texture t;
	Sprite sprite;
	String name;
	float CurrentFrame;
	Clock clock;
	int shoot = 0;

	class Bullet {
	public:

		bool life;
		Clock clock;
		float time;
		FloatRect bullet_rect;
		Image im;
		Texture t;
		Sprite sprite;

		int direction;
		float dx, dy;
		Bullet(FloatRect rect, float loc_dx);
		void WithMap();
		~Bullet();

		void WithPlayer(Player &p);
		void drawing();

	};


};


class Pushka : public Push {
public:

	Pushka(int x, int y);

};