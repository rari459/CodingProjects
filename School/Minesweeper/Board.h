#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Tile.h"

class Board
{
	int width, height, mineCount;
	vector<vector<Tile>> board;

public:

	Board();
	Board(int width, int height, int mineCount);
	vector<vector<Tile>>& getTiles();
	int getColumns();
	int getRows();
	int numberofMines();
	void setBoardImages(sf::RenderWindow& window);
	void floodMines();
	void clear();
	void debug(sf::RenderWindow& window);
	void setAdjacentMines();
	void recursiveClick(int i, int j);
	int numFlags();
	int calculateMines();

	void testBoard(string filename);
	bool checkOverFlow(int row, int column);

	void defeat(sf::RenderWindow& window);
	bool winCheck();
	void win(sf::RenderWindow& window);


};

void drawIcons(sf::RenderWindow& window);

void mineCounter(int Mines, int numFlags, sf::RenderWindow& window);