#pragma once
#include "globals.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

using namespace sf;

class Map {
public:
	Map();
	~Map();
	void drawing();

private:
	Image image1;
	Texture map;//текстура карты
	Sprite s_map;//создаём спрайт для карты

};
