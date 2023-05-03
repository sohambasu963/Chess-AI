#include <iostream>
#include "../include/Board.h"

using namespace std;

Board::Board(int width, int height) : boardWidth(width), boardHeight(height) {}

void Board::loadBoardImage(const string &filePath, const float windowWidth) {
    if (!boardTexture.loadFromFile(filePath)) {
        cout << "Error loading board image" << endl;
    }
    boardSprite.setTexture(boardTexture);
    boardSprite.setScale(boardWidth / boardSprite.getLocalBounds().width,
                         boardHeight / boardSprite.getLocalBounds().height);
    float offset = (windowWidth - boardWidth) / 2.0f;
    boardSprite.setPosition(offset, 0);
}

void Board::initCoords(float blackBuffer, float boardBuffer, float squareSize) {
    square = squareSize;
    for (int i = 0; i < 8; i++) {
        rowCoords[i] = blackBuffer + boardBuffer + (squareSize * i);
        colCoords[i] = boardBuffer + (squareSize * i);
    }
}

void Board::loadPieces(sf::Sprite (&pieces)[32], sf::Texture &texture) {
    const int pieceCutoutSize = 56;
    const float pieceSize = (square * 0.7f) / pieceCutoutSize;
    const int pieceValues[32] = {-1, -2, -3, -4, -5, -3, -2, -1,
                                 -6, -6, -6, -6, -6, -6, -6, -6,
                                 6,  6,  6,  6,  6,  6,  6,  6,
                                 1,  2,  3,  4,  5,  3,  2,  1};
    int index = 0;
    for (auto &piece : pieces) {
        int x = abs(pieceValues[index]) - 1;
        int y = pieceValues[index] > 0 ? 1 : 0;
        piece.setTexture(texture);
        piece.setTextureRect(sf::IntRect(pieceCutoutSize * x, pieceCutoutSize * y,
                                                 pieceCutoutSize, pieceCutoutSize));
        if (index < 8) {
            piece.setPosition(rowCoords[index], colCoords[0]);
        } else if (index < 16) {
            piece.setPosition(rowCoords[index - 8], colCoords[1]);
        } else if (index < 24) {
            piece.setPosition(rowCoords[index - 16], colCoords[6]);
        } else {
            piece.setPosition(rowCoords[index - 24], colCoords[7]);
        }

        piece.setScale(pieceSize, pieceSize);
        index++;
    }
}



sf::Vector2i Board::getPosition(int pieceNumber) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (map[i][j] == pieceNumber) {
                return sf::Vector2i(i, j);
            }
        }
    }
    return sf::Vector2i(-1, -1); // piece not on the board
}

void Board::draw(sf::RenderWindow& window) {
    window.draw(boardSprite);
}
