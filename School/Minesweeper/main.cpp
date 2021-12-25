#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "TextureManager.h"
#include "Tile.h"
#include "Board.h"
using namespace std;




int main()
{

    ifstream inFile("boards/config.cfg");
    string c, r, m;
    getline(inFile, c);
    getline(inFile, r);
    getline(inFile, m);
    int columns = stoi(c);
    int rows = stoi(r);
    int mines = stoi(m);






    cout << "Program Start" << endl;

    //cout << gameBoard.getColumns() << endl;
    //cout << gameBoard.getRows() << endl;
    sf::RenderWindow window(sf::VideoMode(columns * 32, rows * 32 + 88), "Minesweeper");

    Board gameBoard(columns, rows, mines);
    gameBoard.floodMines();
    gameBoard.setAdjacentMines();
    bool reset = false;
    bool debug = false;
    bool test1 = false;
    bool test2 = false;
    bool test3 = false;
    bool defeat = false;

    while (window.isOpen())
    {

        window.clear();


        if (reset) {
            gameBoard.clear();
            gameBoard.floodMines();
            gameBoard.setAdjacentMines();
            reset = false;
            defeat = false;
        }


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;
                    int i = (x + 1) / 32;
                    int j = (y + 1) / 32;
                    if (!gameBoard.getTiles()[j][i].getClicked()) {
                        gameBoard.getTiles()[j][i].toggleFlags();
                    }


                }
                else if (event.mouseButton.button == sf::Mouse::Left) {
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;
                    int i = (x + 1) / 32;
                    int j = (y + 1) / 32;
                    if (x < columns * 32 && y < rows * 32) {
                        if (!gameBoard.getTiles()[j][i].getFlags() && !gameBoard.getTiles()[j][i].getMines() && !gameBoard.getTiles()[j][i].getClicked() && !gameBoard.winCheck() && !defeat) {
                            gameBoard.getTiles()[j][i].Clicked();
                            if (gameBoard.getTiles()[j][i].adjacentMines() == 0) {
                                gameBoard.recursiveClick(j, i);
                            }
                        }
                        else if (!gameBoard.getTiles()[j][i].getFlags() && gameBoard.getTiles()[j][i].getMines() && !gameBoard.getTiles()[j][i].getClicked() && !gameBoard.winCheck() && !defeat)
                            //gameBoard.getTiles()[j][i].Clicked();
                            //gameBoard.getTiles()[j][i].drawMine();
                            defeat = true;
                    }
                    else if (((x - (window.getSize().x - 256)) <= 64) && ((y - (window.getSize().y - 88)) <= 64) && !gameBoard.winCheck() && !defeat) {
                        debug = !debug;
                    }
                    else if (((x - (window.getSize().x / 2 - 32)) <= 64) && ((y - (window.getSize().y - 88)) <= 64)) {
                        reset = !reset;
                    }
                    else if (((x - (window.getSize().x - 192)) <= 64) && ((y - (window.getSize().y - 88)) <= 64)) {
                        test1 = true;
                    }
                    else if (((x - (window.getSize().x - 128)) <= 64) && ((y - (window.getSize().y - 88)) <= 64)) {
                        test2 = true;
                    }
                    else if (((x - (window.getSize().x - 64)) <= 64) && ((y - (window.getSize().y - 88)) <= 64)) {
                        test3 = true;
                    }
                    else {
                        continue;
                    }
                }
            }
        }

        gameBoard.setBoardImages(window);
        drawIcons(window);

        if (debug) {
            gameBoard.debug(window);
        }

        if (test1) {
            gameBoard.testBoard("boards/testboard1.brd");
            gameBoard.setAdjacentMines();
            test1 = false;
            defeat = false;
        }
        if (test2) {
            gameBoard.testBoard("boards/testboard2.brd");
            gameBoard.setAdjacentMines();
            test2 = false;
            defeat = false;
        }
        if (test3) {
            gameBoard.testBoard("boards/testboard3.brd");
            gameBoard.setAdjacentMines();
            test3 = false;
            defeat = false;
        }
        if (defeat) {
            gameBoard.defeat(window);
            debug = false;
        }
        if (gameBoard.winCheck()) {
            gameBoard.win(window);
            mineCounter(0, 0, window);
        }

        mineCounter(gameBoard.calculateMines(), gameBoard.numFlags(), window);


        window.display();



    }
    cout << "Program Closed" << endl;
    TextureManager::Clear();
    return 0;
}



