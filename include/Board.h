#include <SFML/Graphics.hpp>
using namespace std;

class Board {
public:
    Board(int width, int height);
    void loadBoardImage(const string &filePath, float windowWidth);
    void initCoords(float blackBuffer, float boardBuffer, float SquareSize);
    void loadPieces(sf::Sprite (&pieces)[32], sf::Texture &texture);
    void movePiece(sf::Vector2i mousePos,  sf::Sprite &piece, int pieceNum);
    bool isValidMove(int pieceType, sf::Vector2i oldPos, sf::Vector2i newPos);
    int getPieceType(int pieceNum);
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
    int map[8][8] = {  0,  1,  2,  3,  4,  5,  6,  7,
                       8,  9, 10, 11, 12, 13, 14, 15,
                       -1, -1, -1, -1, -1, -1, -1, -1,
                       -1, -1, -1, -1, -1, -1, -1, -1,
                       -1, -1, -1, -1, -1, -1, -1, -1,
                       -1, -1, -1, -1, -1, -1, -1, -1,
                       16, 17, 18, 19, 20, 21, 22, 23,
                       24, 25, 26, 27, 28, 29, 30, 31 };

};
