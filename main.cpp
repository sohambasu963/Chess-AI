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

    // Game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
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




