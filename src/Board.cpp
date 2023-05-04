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
                                 6, 6, 6, 6, 6, 6, 6, 6,
                                 1, 2, 3, 4, 5, 3, 2, 1};
    int index = 0;
    for (auto &piece: pieces) {
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


void Board::movePiece(sf::Vector2i mousePos,  sf::Sprite &piece, int pieceNum) {
    float minDx = abs(mousePos.x - rowCoords[0]);
    float minDy = abs(mousePos.y - colCoords[0]);
    int rowX = 0;
    int colY = 0;
    for (int i = 0; i < 8; i++) {
        if (abs(mousePos.x - rowCoords[i]) < minDx) {
            minDx = abs(mousePos.x - rowCoords[i]);
            rowX = i;
        }
        if (abs(mousePos.y - colCoords[i]) < minDy) {
            minDy = abs(mousePos.y - colCoords[i]);
            colY = i;
        }
    }

    int pieceType = getPieceType(pieceNum);
    sf::Vector2i oldPos = getPosition(pieceNum);
    sf::Vector2i newPos = sf::Vector2i(rowX, colY);
    if (isValidMove(pieceType, oldPos, newPos)) {
        piece.setPosition(rowCoords[newPos.x], colCoords[newPos.y]);
    } else {
        piece.setPosition(rowCoords[oldPos.x], colCoords[oldPos.y]);
    }
}

bool Board::isValidMove(int pieceType, sf::Vector2i oldPos, sf::Vector2i newPos) {
    int dx = (newPos.x - oldPos.x);
    int dy = (newPos.y - oldPos.y);

    if (dy == 0 and dx == 0) {
        return true;
    }

    return false;
}

int Board::getPieceType(int pieceNum) {
    if (pieceNum == 0 or pieceNum == 7) {
        return -1;
    }
    else if (pieceNum == 1 or pieceNum == 6) {
        return -2;
    }
    else if (pieceNum == 2 or pieceNum == 5) {
        return -3;
    }
    else if (pieceNum == 3) {
        return -4;
    }
    else if (pieceNum == 4) {
        return -5;
    }
    else if (8 <= pieceNum && pieceNum < 16) {
        return -6;
    }
    else if (16 <= pieceNum && pieceNum < 24) {
        return 6;
    }
    else if (pieceNum == 28) {
        return 5;
    }
    else if (pieceNum == 27) {
        return 4;
    }
    else if (pieceNum == 26 or pieceNum == 29) {
        return 3;
    }
    else if (pieceNum == 25 or pieceNum == 30) {
        return 2;
    }
    else if (pieceNum == 24 or pieceNum == 31) {
        return 1;
    }
    return 0;
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
