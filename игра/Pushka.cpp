#include "SFML/Graphics.hpp" 
#include <iostream> 
#include "map.h" 
#include "globals.h" 
#include "player.h" 
#include "Pushka.h"



pushka::pushka(int x, int y) {
	t.loadFromFile("images/dogs.png");
	sprite.setTexture(t);
	sprite.setTextureRect(IntRect(0, 0, 23, 23));
	rect = FloatRect(x * 32, y * 32, 0, 0);
	dy = 0;
}

void Push::drawing(float pX, float pY, Player & playerhp)
{
	time = clock.getElapsedTime().asMicroseconds();
	clock.restart();

	time = time / 800;


	sprite.setPosition(rect.left, rect.top);

	rect.left = rect.left + dx * time;
	rect.top = rect.top + dy * time;



	window.draw(sprite);

	if ((pY >= (rect.top - 15)) && (pY <= (rect.top + 32 + 15)) && (pX >= (rect.left - 15) && (pX <= (rect.left + 32 + 15)))) {
		
	}

}
FloatRect Push::FL() {
	return rect;
}
float Push::DX() {
	return dx;
}

Push::Bullet::Bullet(FloatRect rect, float loc_dx) {
	bullet_rect = rect;
	life = true;
	im.loadFromFile("images/pula.png");
	im.createMaskFromColor(Color::Black);
	t.loadFromImage(im);
	sprite.setTexture(t);
	dx = loc_dx * (-3);

}

void Push::Bullet::drawing() {
	time = clock.getElapsedTime().asMicroseconds();
	clock.restart();

	time = time / 400;

	sprite.setPosition(bullet_rect.left, bullet_rect.top);
	bullet_rect.left = bullet_rect.left + dx * time;

	collisionBullet();

	window.draw(sprite);
}

//////////????????? ??? 0 ?? ?????(?????)
void Push::Bullet::collisionBullet() {

	for (int i = (bullet_rect.top) / 32; i < (bullet_rect.top + 32) / 32; i++)
		for (int j = (bullet_rect.left) / 32; j < (bullet_rect.left + 32) / 32; j++)
		{
			if (TileMap[i][j] == '0')
			{
				life = false;
			}
		}

}

Push::Bullet::~Bullet() {

}

//////////////////////????????? ??? ?????????????? ? ???????
void Push::Bullet::destroyBall(Player &p) {
	if ((((p.getplayercoordinateX()) >= ((bullet_rect.left))) && ((p.getplayercoordinateX()) <= ((bullet_rect.left) + 10))) && (((p.getplayercoordinateY()) >= (bullet_rect.top)) && ((p.getplayercoordinateY()) <= (bullet_rect.top) + 32))) {
		life = false;
		
		return;
	}
}