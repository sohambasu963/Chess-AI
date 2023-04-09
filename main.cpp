#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;


const string PATH_DIR = "/Users/sohambasu/CLionProjects/chess-ai/";

int board_map[8][8] =
        { -1, -2, -3, -4, -5, -3, -2, -1,
          -6, -6, -6, -6, -6, -6, -6, -6,
          0,  0,  0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,  0,  0,  0,
          6,  6,  6,  6,  6,  6,  6,  6,
          1,  2,  3,  4,  5,  3,  2,  1 };

void resizeBoard(sf::RenderWindow &window, sf::Sprite &sBoard, sf::Texture& tBoard) {
    float boardSize = min(window.getSize().x, window.getSize().y);
    cout << window.getSize().x << " " << window.getSize().y << " " << boardSize << endl;
}


void load_start_position(const int size) {
    int k = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int position = board_map[i][j];
            if (position != 0) {
                int x = abs(position) - 1;
                int y = position > 0 ? 1 : 0;

                k++;

            }
        }
    }
}



int main() {

    // initialize game window
    const int windowWidth = 1500;
    const int windowHeight = 1500;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Chess");

    // load chess board and pieces
    sf::Texture tBoard;
    tBoard.loadFromFile(PATH_DIR + "images/board.png");
    sf::Sprite sBoard(tBoard);
    sBoard.setScale(windowWidth / sBoard.getLocalBounds().width,
                    windowHeight / sBoard.getLocalBounds().height);

    sf::Texture tPieces;
    tPieces.loadFromFile(PATH_DIR + "images/figures.png");
    sf::Sprite sPieces[32];
    for (int i = 0; i < 32; i++) {
        sPieces[i].setTexture(tPieces);
    }
    // load_start_position();

    float boardScale = 0.8f;

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    resizeBoard(window, sBoard, tBoard);
                    break;
                default:
                    break;
            }
        }


        window.clear();
        window.draw(sBoard);
        window.display();
    }

}

