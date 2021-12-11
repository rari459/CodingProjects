#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
using namespace std;

class Tile
{
	int xcor, ycor, adjMines;
	bool flagged, isMine, clicked, drawmine;
public:
	sf::Sprite hiddenTile;
	sf::Sprite revealedTile;
	sf::Sprite flag;
	sf::Sprite mine;
	sf::Sprite num1;
	sf::Sprite num2;
	sf::Sprite num3;
	sf::Sprite num4;
	sf::Sprite num5;
	sf::Sprite num6;
	sf::Sprite num7;
	sf::Sprite num8;
	sf::Sprite num9;

	Tile();
	Tile(int xcor, int ycor);
	int getXPosition();
	int getYPosition();
	bool getFlags();
	void toggleFlags();
	void setFlags(bool flag);
	bool getMines();
	bool isClickedMine();
	void drawMine();
	void setMines(bool mine);
	bool getClicked();
	void Clicked();
	int& adjacentMines();
	Tile& operator= (Tile tile);

};
