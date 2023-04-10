#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;


const string PATH_DIR = "/Users/sohambasu/CLionProjects/chess-ai/";
const int size = 56;
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

// change formula, calculate black space buffer as windowWidth - boardWidth,
//                 calculate board buffer as % of boardWidth or boardHeight
void initBoardCoords(float blackBuffer, float boardBuffer, float boardHeight) {
    float squareSize = (boardHeight - boardBuffer) / 8.0f;
    for (int i = 0; i < 8; i++) {
        rowCoords[i] = blackBuffer + boardBuffer + (squareSize * i);
        colCoords[i] = boardBuffer + (squareSize * i);
    }
}


void loadStartPosition(const int size) {
    int k = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int position = board_map[i][j];
            if (position != 0) {
                int x = abs(position) - 1;
                int y = position > 0 ? 1 : 0;
                sPieces[k].setTextureRect( sf::IntRect(size*x,size*y,size,size) );
                sPieces[k].setPosition(rowCoords[j],colCoords[i]);
                k++;

            }
        }
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
    initBoardCoords((windowWidth - boardWidth) / 2.0f, boardHeight * (75.0f/1440.0f), boardHeight);
    cout << (windowWidth - boardWidth) << endl;
    cout << boardHeight << endl;

    sf::RectangleShape line(sf::Vector2f(650.f, 1.f));
    // 575.f is width of black space
    // 650.f includes the
    for (int i = 0; i < 8; i++)
        cout << rowCoords[i] << " " << colCoords[i] << endl;
    line.setFillColor(sf::Color::Red);
    line.setPosition(0, 300.f); // Center line horizontally, and place it at y=300

    // buffer area of 650.f on both sides or 25% of window width on each side
    // therefore remaining, 50

    sf::Texture tPieces;
    tPieces.loadFromFile(PATH_DIR + "images/figures.png");
    // sf::Sprite sPieces[32];
    for (int i = 0; i < 32; i++) {
        sPieces[i].setTexture(tPieces);
    }
    loadStartPosition(56);

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
        window.draw(line);
        window.display();
    }

}

