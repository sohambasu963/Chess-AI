#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;


const string PATH_DIR = "/Users/sohambasu/CLionProjects/chess-ai/";
sf::Sprite sPieces[32];

int rows[8] = {35, 105, 170, 235, 305, 370, 440, 505 };
int columns[8] = {35, 105, 170, 235, 305, 370, 440, 505 };
// int columns[8] = {40, 105, 175, 240, 305, 375, 440, 510};

int board_map[8][8] =
        { -1, -2, -3, -4, -5, -3, -2, -1,
          -6, -6, -6, -6, -6, -6, -6, -6,
          0,  0,  0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,  0,  0,  0,
          6,  6,  6,  6,  6,  6,  6,  6,
          1,  2,  3,  4,  5,  3,  2,  1 };

// float board_coords[8][8] = {};
float rowCoords[8] = {};
float colCoords[8] = {};


void initBoardCoords(float blackBuffer, float boardBuffer, float squareSize) {
    for (int i = 0; i < 8; i++) {
        rowCoords[i] = blackBuffer + boardBuffer + (squareSize * i);
        colCoords[i] = boardBuffer + (squareSize * i);
    }
}


void loadStartPosition(const int pieceCutoutSize) {
    int k = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int position = board_map[i][j];
            if (position != 0) {
                int x = abs(position) - 1;
                int y = position > 0 ? 1 : 0;
                // sPieces[k].setTexture(tPieces);
                sPieces[k].setTextureRect(sf::IntRect(pieceCutoutSize*x,pieceCutoutSize*y,
                                                      pieceCutoutSize,pieceCutoutSize));
                sPieces[k].setPosition(rowCoords[j],colCoords[i]);
                k++;

            }
        }
    }
}

void initGame(float blackBuffer, float boardHeight) {
    float boardBuffer = boardHeight * (125.0f/1440.0f) * 0.83f;
    float squareSize = ((boardHeight - boardBuffer) / 8.0f) * 0.96f;
    initBoardCoords(blackBuffer, boardBuffer, squareSize);

    const int pieceCutoutSize = 56;
    loadStartPosition(pieceCutoutSize);

    float pieceSize = (squareSize * 0.7f) / pieceCutoutSize;
    for (int i = 0; i < 32; i ++) {
        sPieces[i].setScale(pieceSize, pieceSize);
    }
}


int main() {
    // initialize game window
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    float windowWidth = desktop.width * 0.9f;
    float windowHeight = desktop.height * 0.8f;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Chess",
                            sf::Style::Close);
    float boardWidth= min(windowWidth , windowHeight);
    float boardHeight = min(windowWidth, windowHeight);

    // load chess board and pieces
    sf::Texture tBoard;
    tBoard.loadFromFile(PATH_DIR + "images/board.png");
    sf::Sprite sBoard(tBoard);
    sBoard.setScale(boardWidth / sBoard.getLocalBounds().width,
                    boardHeight / sBoard.getLocalBounds().height);

    float offsetX = (windowWidth - boardWidth) / 2.0f;
    float offsetY = (windowHeight - boardHeight) / 2.0f;
    sBoard.setPosition(offsetX, offsetY);

    sf::Texture tPieces;
    tPieces.loadFromFile(PATH_DIR + "images/figures.png");
    for (auto & sPiece : sPieces) {
        sPiece.setTexture(tPieces);
    }

    initGame(offsetX, boardHeight);


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
                        cout << rowX << " " << colY << endl;
                        sPieces[current_piece].setPosition(rowCoords[rowX], colCoords[colY]);
                    }
                    break;
                default:
                    break;
            }
        }
        if (pieceMoving) {
            sPieces[current_piece].setPosition(mousePos.x - dx, mousePos.y - dy);
        }

        window.clear();
        window.draw(sBoard);
        for (const auto & sPiece : sPieces) {
            window.draw(sPiece);
        }
        // window.draw(line);
        window.display();
    }

}

