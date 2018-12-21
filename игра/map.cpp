#include <SFML/Graphics.hpp>
#include "globals.h"
#include "map.h"
#include <fstream>
#include <string>

RenderWindow window(sf::VideoMode(1400, 700), "GAME");


Map::Map() {//конструктор класса

	image1.loadFromFile("images/map1.png");// загружаем картинку из файла

	map.loadFromImage(image1);//заряжаем текстуру картинкой

	s_map.setTexture(map);//заливаем текстуру спрайтом

	Clock clock;

	

}

Map::~Map() {

}




void Map::drawing() {
	for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(128, 0, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
			if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(32, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
			if ((TileMap[i][j] == 'q')) s_map.setTextureRect(IntRect(96, 0, 32, 32));
			if ((TileMap[i][j] == 'w')) s_map.setTextureRect(IntRect(0, 32, 32, 32));
			if ((TileMap[i][j] == '1')) s_map.setTextureRect(IntRect(0, 0, 32, 32));
			if ((TileMap[i][j] == 'k')) s_map.setTextureRect(IntRect(128, 64, 32, 32));
			if ((TileMap[i][j] == 'c')) s_map.setTextureRect(IntRect(128, 96, 32, 32));
			if ((TileMap[i][j] == 'x')) s_map.setTextureRect(IntRect(96, 0, 32, 32));
			if ((TileMap[i][j] == '[')) s_map.setTextureRect(IntRect(128, 128, 32, 32));
			if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 160, 32, 32));


			s_map.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один 

			window.draw(s_map);//рисуем квадратики на экран


		}
}

String TileMap[HEIGHT_MAP] = {// определение карты (объявление и инициализация, на случай, если загрузка не сработает)

    "0000000000000000000000000000000000",
	"0w                               0",
	"0  0q0q0q000q0q0q0000q000000q000q0",
	"0  0q0 hq0  q0q0q0   q00    q0q0q0",
	"0  0q0q0q0q000q0q0q00000q000q0q0q0",
	"0  0q0q0q0q0q0q0q0q0  q0q000q0q0q0",
	"0  0q0q0q0q0q0q0q0q0q0q0    q0q0q0",
	"0  0q0q0q0q0q0 0q0  q0q0q00000q0q0",
	"0     q0q0q0q000q00000q0q0    q0q0",
	"0     q0q0      q0    q0q0q000q0q0",
	"000q00q0q0000000q0q000q0  q0q0q0q0",
	"0  q0 q0   q0 y q0q0  q0000sq0q0q0",
	"0q0q0q00000q0q0000q0q000  q0q0k q0",
	"0q0q0q0  q0q0q0 q0q0  q0q0q0q000q0",
	"0q0q0q0q0q0q0q0q00q000q0q0      q0",
	"0q0q0q0q0q0q0q0q0hq0  q0q0000000q0",
	"0q0q0q0q0q0q0q0q0q00q000      q0x0",
	"0q0q0q0q0q0q0q0q0q0 q000000000q0c0",
	"0h q0  q0  q0  q0             q010",
	"0000000000000000000000000000000000",

};