#include <SFML/Graphics.hpp>
using namespace std;

class Board {
public:
    Board(int width, int height);
    void loadBoardImage(const string &filePath, float windowWidth);
    void initCoords(float blackBuffer, float boardBuffer, float SquareSize);
    void loadPieces(sf::Sprite (&pieces)[32], sf::Texture &texture);
    sf::Vector2i getPosition(int pieceNumber);
    void draw(sf::RenderWindow& window);

private:
    sf::Texture boardTexture;
    sf::Sprite boardSprite;
    int boardWidth;
    int boardHeight;
    float square;
    float rowCoords[8];
    float colCoords[8];
    int map[8][8] = { -1, -2, -3, -4, -5, -3, -2, -1,
                      -6, -6, -6, -6, -6, -6, -6, -6,
                      0,  0,  0,  0,  0,  0,  0,  0,
                      0,  0,  0,  0,  0,  0,  0,  0,
                      0,  0,  0,  0,  0,  0,  0,  0,
                      0,  0,  0,  0,  0,  0,  0,  0,
                      6,  6,  6,  6,  6,  6,  6,  6,
                      1,  2,  3,  4,  5,  3,  2,  1 };
};
