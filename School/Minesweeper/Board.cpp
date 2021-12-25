#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "TextureManager.h"
#include "Tile.h"
#include "Board.h"
#include "Random.h"



Board::Board() {
}

Board::Board(int width, int height, int mineCount) {
	this->mineCount = mineCount;
	this->height = height;
	this->width = width;

	for (unsigned int i = 0; i < height; i++) {
		vector<Tile> temp;
		for (unsigned int j = 0; j < width; j++) {
			Tile tile(j * 32, i * 32);
			temp.push_back(tile);
		}
		board.push_back(temp);
	}

}

vector<vector<Tile>>& Board::getTiles() {
	return board;
}

int Board::getColumns() {
	return width;
}

int Board::getRows() {
	return height;
}

int Board::numberofMines() {
	return mineCount;
}

void Board::floodMines() {
	for (unsigned int i = 0; i < this->numberofMines(); i++) {
		int mineColumn = Random::Int(0, getColumns() - 1);
		int mineRow = Random::Int(0, getRows() - 1);
		if (getTiles()[mineRow][mineColumn].getMines()) {
			i--;
		}
		else {
			getTiles()[mineRow][mineColumn].setMines(true);
		}
	}
}

void Board::clear() {
	getTiles().clear();
	for (unsigned int i = 0; i < height; i++) {
		vector<Tile> temp;
		for (unsigned int j = 0; j < width; j++) {
			Tile tile(j * 32, i * 32);
			temp.push_back(tile);
		}
		getTiles().push_back(temp);
	}
}

void Board::setBoardImages(sf::RenderWindow& gameWindow) {
	for (unsigned int i = 0; i < this->getRows(); i++) {
		for (unsigned int j = 0; j < this->getColumns(); j++) {
			Tile tile = getTiles()[i][j];
			if (!tile.isClickedMine() && !tile.getClicked() && !tile.getFlags()) {
				tile.hiddenTile.setPosition(tile.getXPosition(), tile.getYPosition());
				gameWindow.draw(tile.hiddenTile);

			}
			if (!tile.getMines() && !tile.getFlags() && tile.getClicked()) {
				tile.revealedTile.setPosition(tile.getXPosition(), tile.getYPosition());
				gameWindow.draw(tile.revealedTile);
				if (tile.adjacentMines() == 1) {
					tile.num1.setPosition(tile.getXPosition(), tile.getYPosition());
					gameWindow.draw(tile.num1);
				}
				else if (tile.adjacentMines() == 2) {
					tile.num2.setPosition(tile.getXPosition(), tile.getYPosition());
					gameWindow.draw(tile.num2);
				}
				else if (tile.adjacentMines() == 3) {
					tile.num3.setPosition(tile.getXPosition(), tile.getYPosition());
					gameWindow.draw(tile.num3);
				}
				else if (tile.adjacentMines() == 4) {
					tile.num4.setPosition(tile.getXPosition(), tile.getYPosition());
					gameWindow.draw(tile.num4);
				}
				else if (tile.adjacentMines() == 5) {
					tile.num5.setPosition(tile.getXPosition(), tile.getYPosition());
					gameWindow.draw(tile.num5);
				}
				else if (tile.adjacentMines() == 6) {
					tile.num6.setPosition(tile.getXPosition(), tile.getYPosition());
					gameWindow.draw(tile.num6);
				}
				else if (tile.adjacentMines() == 7) {
					tile.num7.setPosition(tile.getXPosition(), tile.getYPosition());
					gameWindow.draw(tile.num7);
				}
				else if (tile.adjacentMines() == 8) {
					tile.num8.setPosition(tile.getXPosition(), tile.getYPosition());
					gameWindow.draw(tile.num8);
				}
			}
			else if (!tile.isClickedMine() && tile.getFlags() && !tile.getClicked()) {
				tile.revealedTile.setPosition(tile.getXPosition(), tile.getYPosition());
				gameWindow.draw(tile.revealedTile);
				tile.flag.setPosition(tile.getXPosition(), tile.getYPosition());
				gameWindow.draw(tile.flag);
			}
			else if (tile.isClickedMine()) {
				tile.revealedTile.setPosition(tile.getXPosition(), tile.getYPosition());
				gameWindow.draw(tile.revealedTile);
				tile.mine.setPosition(tile.getXPosition(), tile.getYPosition());
				gameWindow.draw(tile.mine);
			}
		}
	}
}

void Board::debug(sf::RenderWindow& gameWindow) {
	for (unsigned int i = 0; i < this->getRows(); i++) {
		for (unsigned int j = 0; j < this->getColumns(); j++) {
			Tile tile = getTiles()[i][j];
			if (tile.getMines()) {
				tile.revealedTile.setPosition(tile.getXPosition(), tile.getYPosition());
				gameWindow.draw(tile.revealedTile);
				tile.mine.setPosition(tile.getXPosition(), tile.getYPosition());
				gameWindow.draw(tile.mine);
			}
		}
	}
}

void drawIcons(sf::RenderWindow& window) {
	sf::Sprite test1;
	sf::Sprite test2;
	sf::Sprite test3;
	sf::Sprite debug;
	sf::Sprite smiley;

	smiley.setTexture(TextureManager::GetTexture("face_happy"));
	smiley.setPosition(window.getSize().x / 2 - 32, window.getSize().y - 88);
	window.draw(smiley);

	test1.setTexture(TextureManager::GetTexture("test_1"));
	test1.setPosition(window.getSize().x - 192, window.getSize().y - 88);
	window.draw(test1);
	test2.setTexture(TextureManager::GetTexture("test_2"));
	test2.setPosition(window.getSize().x - 128, window.getSize().y - 88);
	window.draw(test2);
	test3.setTexture(TextureManager::GetTexture("test_3"));
	test3.setPosition(window.getSize().x - 64, window.getSize().y - 88);
	window.draw(test3);

	debug.setTexture(TextureManager::GetTexture("debug"));
	debug.setPosition(window.getSize().x - 256, window.getSize().y - 88);
	window.draw(debug);

}

void Board::setAdjacentMines() {
	for (unsigned int i = 0; i < this->getRows(); i++) {
		for (unsigned int j = 0; j < this->getColumns(); j++) {
			if (!getTiles()[i][j].getMines())
				if (checkOverFlow(i - 1, j - 1) && getTiles()[i - 1][j - 1].getMines())
					getTiles()[i][j].adjacentMines() += 1;
			if (checkOverFlow(i - 1, j) && getTiles()[i - 1][j].getMines())
				getTiles()[i][j].adjacentMines() += 1;
			if (checkOverFlow(i - 1, j + 1) && getTiles()[i - 1][j + 1].getMines())
				getTiles()[i][j].adjacentMines() += 1;
			if (checkOverFlow(i, j - 1) && getTiles()[i][j - 1].getMines())
				getTiles()[i][j].adjacentMines() += 1;
			if (checkOverFlow(i, j + 1) && getTiles()[i][j + 1].getMines())
				getTiles()[i][j].adjacentMines() += 1;
			if (checkOverFlow(i + 1, j - 1) && getTiles()[i + 1][j - 1].getMines())
				getTiles()[i][j].adjacentMines() += 1;
			if (checkOverFlow(i + 1, j) && getTiles()[i + 1][j].getMines())
				getTiles()[i][j].adjacentMines() += 1;
			if (checkOverFlow(i + 1, j + 1) && getTiles()[i + 1][j + 1].getMines())
				getTiles()[i][j].adjacentMines() += 1;
		}
	}
}

void Board::recursiveClick(int i, int j) {
	if (checkOverFlow(i - 1, j - 1) && !getTiles()[i - 1][j - 1].getMines() && !getTiles()[i - 1][j - 1].getClicked() && !getTiles()[i - 1][j - 1].getFlags()) {
		getTiles()[i - 1][j - 1].Clicked();
		if (getTiles()[i - 1][j - 1].adjacentMines() == 0)
			recursiveClick(i - 1, j - 1);
	}
	if (checkOverFlow(i - 1, j) && !getTiles()[i - 1][j].getMines() && !getTiles()[i - 1][j].getClicked() && !getTiles()[i - 1][j].getFlags()) {
		getTiles()[i - 1][j].Clicked();
		if (getTiles()[i - 1][j].adjacentMines() == 0)
			recursiveClick(i - 1, j);
	}
	if (checkOverFlow(i - 1, j + 1) && !getTiles()[i - 1][j + 1].getMines() && !getTiles()[i - 1][j + 1].getClicked() && !getTiles()[i - 1][j + 1].getFlags()) {
		getTiles()[i - 1][j + 1].Clicked();
		if (getTiles()[i - 1][j + 1].adjacentMines() == 0)
			recursiveClick(i - 1, j + 1);
	}
	if (checkOverFlow(i, j - 1) && !getTiles()[i][j - 1].getMines() && !getTiles()[i][j - 1].getClicked() && !getTiles()[i][j - 1].getFlags()) {
		getTiles()[i][j - 1].Clicked();
		if (getTiles()[i][j - 1].adjacentMines() == 0)
			recursiveClick(i, j - 1);
	}
	if (checkOverFlow(i, j + 1) && !getTiles()[i][j + 1].getMines() && !getTiles()[i][j + 1].getClicked() && !getTiles()[i][j + 1].getFlags()) {
		getTiles()[i][j + 1].Clicked();
		if (getTiles()[i][j + 1].adjacentMines() == 0)
			recursiveClick(i, j + 1);
	}
	if (checkOverFlow(i + 1, j - 1) && !getTiles()[i + 1][j - 1].getMines() && !getTiles()[i + 1][j - 1].getClicked() && !getTiles()[i + 1][j - 1].getFlags()) {
		getTiles()[i + 1][j - 1].Clicked();
		if (getTiles()[i + 1][j - 1].adjacentMines() == 0)
			recursiveClick(i + 1, j - 1);
	}
	if (checkOverFlow(i + 1, j) && !getTiles()[i + 1][j].getMines() && !getTiles()[i + 1][j].getClicked() && !getTiles()[i + 1][j].getFlags()) {
		getTiles()[i + 1][j].Clicked();
		if (getTiles()[i + 1][j].adjacentMines() == 0)
			recursiveClick(i + 1, j);
	}
	if (checkOverFlow(i + 1, j + 1) && !getTiles()[i + 1][j + 1].getMines() && !getTiles()[i + 1][j + 1].getClicked() && !getTiles()[i + 1][j + 1].getFlags()) {
		getTiles()[i + 1][j + 1].Clicked();
		if (getTiles()[i + 1][j + 1].adjacentMines() == 0)
			recursiveClick(i + 1, j + 1);
	}

}

void Board::testBoard(string filename) {
	ifstream testFile(filename);
	this->clear();
	char c;
	vector <char> charList;
	while (testFile.get(c)) {
		charList.push_back(c);
	}

	int k = 0;
	for (unsigned int i = 0; i < this->getRows(); i++) {
		for (unsigned int j = 0; j < this->getColumns(); j++) {
			if (charList[k] == '1') {
				board[i][j].setMines(true);
			}
			k++;
		}
		k++;
	}
}

bool Board::checkOverFlow(int row, int column) {
	return (row >= 0 && column >= 0 && (row < board.size()) && (column < board[0].size()));
}

int Board::numFlags() {
	int flagCount = 0;
	for (unsigned int i = 0; i < this->getRows(); i++) {
		for (unsigned int j = 0; j < this->getColumns(); j++) {
			if (getTiles()[i][j].getFlags()) {
				flagCount++;
			}
		}
	}
	return flagCount;
}

void Board::defeat(sf::RenderWindow& window) {
	sf::Sprite dead;
	dead.setTexture(TextureManager::GetTexture("face_lose"));
	dead.setPosition(window.getSize().x / 2 - 32, window.getSize().y - 88);
	window.draw(dead);


	for (unsigned int i = 0; i < this->getRows(); i++) {
		for (unsigned int j = 0; j < this->getColumns(); j++) {
			getTiles()[i][j].setFlags(false);
			if (getTiles()[i][j].getMines()) {
				getTiles()[i][j].drawMine();
			}
		}
	}
}

bool Board::winCheck() {
	bool win = true;


	for (unsigned int i = 0; i < this->getRows(); i++) {
		for (unsigned int j = 0; j < this->getColumns(); j++) {
			if (!getTiles()[i][j].getMines() && !getTiles()[i][j].getClicked()) {
				win = false;
			}
		}
	}

	return win;

}

void Board::win(sf::RenderWindow& window) {
	sf::Sprite glasses;
	glasses.setTexture(TextureManager::GetTexture("face_win"));
	glasses.setPosition(window.getSize().x / 2 - 32, window.getSize().y - 88);
	window.draw(glasses);

	for (unsigned int i = 0; i < this->getRows(); i++) {
		for (unsigned int j = 0; j < this->getColumns(); j++) {
			if (getTiles()[i][j].getMines()) {
				getTiles()[i][j].setFlags(true);
			}
		}
	}
}

int Board::calculateMines() {
	int numMines = 0;
	for (unsigned int i = 0; i < this->getRows(); i++) {
		for (unsigned int j = 0; j < this->getColumns(); j++) {
			if (getTiles()[i][j].getMines()) {
				numMines++;
			}
		}
	}
	return numMines;
}

void mineCounter(int Mines, int numFlags, sf::RenderWindow& window) {
	sf::Sprite hunDigit;
	sf::Sprite tensDigit;
	sf::Sprite onesDigit;
	sf::Sprite minusSign;
	int diff = Mines - numFlags;
	int hun = diff / 100;
	int ten = (diff % 100) / 10;
	int one = (diff % 10);

	minusSign.setTexture(TextureManager::GetTexture("digits"));
	minusSign.setTextureRect(sf::IntRect(210, 0, 21, 32));
	minusSign.setPosition(0, window.getSize().y - 88);

	hunDigit.setTexture(TextureManager::GetTexture("digits"));
	hunDigit.setTextureRect(sf::IntRect(abs(hun) * 21, 0, 21, 32));
	hunDigit.setPosition(21, window.getSize().y - 88);

	tensDigit.setTexture(TextureManager::GetTexture("digits"));
	tensDigit.setTextureRect(sf::IntRect(abs(ten) * 21, 0, 21, 32));
	tensDigit.setPosition(42, window.getSize().y - 88);

	onesDigit.setTexture(TextureManager::GetTexture("digits"));
	onesDigit.setTextureRect(sf::IntRect(abs(one) * 21, 0, 21, 32));
	onesDigit.setPosition(63, window.getSize().y - 88);

	if (diff < 0) {
		window.draw(minusSign);
	}
	window.draw(hunDigit);
	window.draw(tensDigit);
	window.draw(onesDigit);
}