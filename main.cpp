#include <iostream>
#include <SFML/Graphics.hpp>
#include "./include/Board.h"
using namespace std;

const string PATH_DIR = "/Users/sohambasu/CLionProjects/chess-ai/";

void initGame(Board board, float blackBuffer, float boardHeight) {
    float boardBuffer = boardHeight * (125.0f/1440.0f) * 0.83f;
    float squareSize = ((boardHeight - boardBuffer) / 8.0f) * 0.96f;
    board.initCoords(blackBuffer, boardBuffer, squareSize);
}

int main() {
    // Create a window
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    float windowWidth = desktop.width * 0.9f;
    float windowHeight = desktop.height * 0.8f;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Chess",
                            sf::Style::Close);

    float boardWidth = min(windowWidth, windowHeight);
    float boardHeight = boardWidth;

    Board board(boardWidth, boardHeight);
    board.loadBoardImage(PATH_DIR + "images/board.png", windowWidth);

    float offset = (windowWidth - boardWidth) / 2.0f;
    float boardBuffer = boardHeight * (125.0f/1440.0f) * 0.83f;
    float squareSize = ((boardHeight - boardBuffer) / 8.0f) * 0.96f;
    board.initCoords(offset, boardBuffer, squareSize);

    sf::Texture tPieces;
    sf::Sprite sPieces[32];
    tPieces.loadFromFile(PATH_DIR + "images/figures.png");

    board.loadPieces(sPieces, tPieces);

    float dx, dy;
    bool pieceMoving = false;
    int current_piece;
    while (window.isOpen()) {

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if (event.key.code == sf::Mouse::Left) {
                        for (int i = 0; i < 32; i++) {
                            if (sPieces[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                current_piece = i;
                                pieceMoving = true;
                                dx = mousePos.x - sPieces[i].getPosition().x;
                                dy = mousePos.y - sPieces[i].getPosition().y;
                            }
                        }
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    if (event.key.code == sf::Mouse::Left) {
                        pieceMoving = false;
                    }
                default:
                    break;
            }
        }
        if (pieceMoving) {
            sPieces[current_piece].setPosition(mousePos.x - dx, mousePos.y - dy);
        }

        window.clear();
        board.draw(window);
        for (const auto & sPiece : sPieces) {
            window.draw(sPiece);
        }
        window.display();
    }

    return 0;
}




