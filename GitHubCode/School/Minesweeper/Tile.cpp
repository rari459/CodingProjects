#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Tile.h"
using namespace std;

Tile::Tile() {
	this->ycor = 0;
	this->xcor = 0;
	clicked = false;
	flagged = false;
	isMine = false;
	adjMines = 0;
	drawmine = false;

	hiddenTile.setTexture(TextureManager::GetTexture("tile_hidden"));
	revealedTile.setTexture(TextureManager::GetTexture("tile_revealed"));
	flag.setTexture(TextureManager::GetTexture("flag"));
	mine.setTexture(TextureManager::GetTexture("mine"));

	num1.setTexture(TextureManager::GetTexture("number_1"));
	num2.setTexture(TextureManager::GetTexture("number_2"));
	num3.setTexture(TextureManager::GetTexture("number_3"));
	num4.setTexture(TextureManager::GetTexture("number_4"));
	num5.setTexture(TextureManager::GetTexture("number_5"));
	num6.setTexture(TextureManager::GetTexture("number_6"));
	num7.setTexture(TextureManager::GetTexture("number_7"));
	num8.setTexture(TextureManager::GetTexture("number_8"));
}

Tile::Tile(int xcor, int ycor) {
	this->ycor = ycor;
	this->xcor = xcor;
	clicked = false;
	flagged = false;
	isMine = false;
	this->adjMines = 0;
	drawmine = false;

	hiddenTile.setTexture(TextureManager::GetTexture("tile_hidden"));
	revealedTile.setTexture(TextureManager::GetTexture("tile_revealed"));
	flag.setTexture(TextureManager::GetTexture("flag"));
	mine.setTexture(TextureManager::GetTexture("mine"));

	num1.setTexture(TextureManager::GetTexture("number_1"));
	num2.setTexture(TextureManager::GetTexture("number_2"));
	num3.setTexture(TextureManager::GetTexture("number_3"));
	num4.setTexture(TextureManager::GetTexture("number_4"));
	num5.setTexture(TextureManager::GetTexture("number_5"));
	num6.setTexture(TextureManager::GetTexture("number_6"));
	num7.setTexture(TextureManager::GetTexture("number_7"));
	num8.setTexture(TextureManager::GetTexture("number_8"));
}

Tile& Tile::operator= (Tile tile) {
	xcor = tile.xcor;
	ycor = tile.ycor;
	adjMines = tile.adjMines;
	flagged = tile.flagged;
	isMine = tile.isMine;
	clicked = tile.clicked;

	return *this;
}

int Tile::getXPosition() {
	return xcor;
}

int Tile::getYPosition() {
	return ycor;
}

bool Tile::getFlags() {
	return flagged;
}

void Tile::toggleFlags() {
	this->flagged = !this->flagged;
}

void Tile::setFlags(bool flag) {
	this->flagged = flag;
}

bool Tile::getMines() {
	return isMine;
}

bool Tile::isClickedMine() {
	return drawmine;
}

void Tile::drawMine() {
	drawmine = true;
}

void Tile::setMines(bool mines) {
	isMine = true;
}

bool Tile::getClicked() {
	return clicked;
}

void Tile::Clicked() {
	this->clicked = true;
}

int& Tile::adjacentMines() {
	return adjMines;
}