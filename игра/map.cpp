#include <SFML/Graphics.hpp>
#include "globals.h"
#include "map.h"
#include <fstream>
#include <string>


using namespace sf;



RenderWindow window(sf::VideoMode(1400, 700), "GAME");//���������������� ������ ���� ����


Map::Map() {//����������� ������

	image1.loadFromFile("images/map1.png");// ��������� �������� �� �����

	map.loadFromImage(image1);//�������� �������� ���������

	s_map.setTexture(map);//�������� �������� ��������

	Clock clock;

	window.clear(Color(33, 30, 30));

}

Map::~Map() {

}




void Map::drawing() {

	for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(128, 0, 32, 32)); //���� ��������� ������ ������, �� ������ 1� ���������
			if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(32, 0, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������
			if ((TileMap[i][j] == 'q')) s_map.setTextureRect(IntRect(96, 0, 32, 32));
			if ((TileMap[i][j] == 'w')) s_map.setTextureRect(IntRect(0, 32, 32, 32));
			if ((TileMap[i][j] == '1')) s_map.setTextureRect(IntRect(0, 0, 32, 32));
			if ((TileMap[i][j] == 'k')) s_map.setTextureRect(IntRect(128, 64, 32, 32));
			if ((TileMap[i][j] == 'c')) s_map.setTextureRect(IntRect(128, 96, 32, 32));
			if ((TileMap[i][j] == 'x')) s_map.setTextureRect(IntRect(96, 0, 32, 32));


			s_map.setPosition(j * 32, i * 32);//�� ���� ����������� ����������, ��������� � �����. �� ���� ������ ������� �� ��� �������. ���� ������, �� ��� ����� ���������� � ����� �������� 32*32 � �� ������ ���� 

			window.draw(s_map);//������ ���������� �� �����


		}
}

String TileMap[HEIGHT_MAP] = {// ����������� ����� (���������� � �������������, �� ������, ���� �������� �� ���������)

	"0000000000000000000000000000000000",
	"0w                              q0",
	"0  0q0q0q000q0q0q0000q000000q0 0q0",
	"0  0q0  q0  q0q0q0   q00    q0q0q0",
	"0  0q0q0q0q000q0q0q00000q000q0q0q0",
	"0  0q0q0q0q0q0q0q0q0  q0q000q0q0q0",
	"0  0q0q0q0q0q0q0q0q0q0q0    q0q0q0",
	"0  0q0q0q0q0q0 0q0  q0q0q00000q0q0",
	"0     q0q0q0q000q00000q0q0    q0q0",
	"0     q0q0      q0    q0q0q000q0q0",
	"000q00q0q0000000q0q000q0  q0q0q0q0",
	"0  q0 q0   q0 y q0q0  q00000q0q0q0",
	"0q0q0q00000q0q0000q0q000  q0q0k0q0",
	"0q0q0q0  q0q0q0 q0q0  q0q0q0q0 0q0",
	"0q0q0q0q0q0q0q0q00q000q0q0      q0",
	"0q0q0q0q0q0q0q0q0 q0  q0q0000000q0",
	"0q0q0q0q0q0q0q0q0q00q000      q0x0",
	"0q0q0q0q0q0q0q0q0q0 q000000000q0c0",
	"0  q0  q0  q0  q0             q010",
	"0000000000000000000000000000000000"
,
};