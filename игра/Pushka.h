#pragma once
#include "SFML/Graphics.hpp" 
#include <iostream> 
#include "player.h" 

using namespace sf;

class Push {
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

	FloatRect FL();
	float DX();

	int shoot = 0;

	class Bullet {//????? ????
	public:

		bool life;
		Clock clock;
		float time;
		FloatRect bullet_rect;
		Image im;
		Texture t;
		Sprite sprite;

		int direction;//??????????? ????
		float dx, dy;
		Bullet(FloatRect rect, float loc_dx);
		~Bullet();
		void collisionBullet();
		void destroyBall(Player &p);
		void drawing();

	};


};


class pushka : public Push {
public:

	pushka(int x, int y);

};
