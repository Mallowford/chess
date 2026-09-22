#include "../header/Chess.hpp"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

enum class Piece_Type {
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King
};

struct Position {
    int row;
    int col;
    Position(int row, int col) : row(row), col(col) {};
};

struct ChessPiece {
    sf::Sprite localSprite;
    bool White = true;
    Piece_Type piece = Piece_Type::Pawn;
    Position pos;
    ChessPiece(const sf::Texture& texture, bool isWhite, Piece_Type type, int row, int col) : localSprite(texture), White(isWhite), piece(type), pos(row, col) {};
};

void CreateBoard(std::vector<sf::RectangleShape>& board);
void pawnRow(std::vector<ChessPiece>& board);
bool move();
std::vector<Position> legal_moves(Piece_Type type, Position starting_position);

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 800}), "Chess", sf::State::Windowed, {sf::Style::Titlebar, sf::Style::Close});
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);

    sf::Clock billyMays;

    std::vector<sf::RectangleShape> map;
    std::vector<ChessPiece> pieces;

    CreateBoard(map);
    pawnRow(pieces);

    // std::cout << sprite.getScale().x << "\n";
    // std::cout << sprite.getScale().y << "\n";

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            };
        };
        if (!window.hasFocus()) { // Lost Focus
            if (billyMays.getElapsedTime().asSeconds() > 1) {
                std::cout << "Not focused!\n";
                billyMays.restart();
            };
        };

        window.clear(sf::Color::Black);

        for (int i = 0; i < map.size(); i++) {
            window.draw(map.at(i));
        };

        for (int i = 0; i < pieces.size(); i++) {
            window.draw(pieces.at(i).localSprite);
        };

        // window.draw(sprite);

        window.display();        
    };

    std::cout << "Program Ended\n";
    return 0;
};

void CreateBoard(std::vector<sf::RectangleShape>& board) {
    for (int i = 0; i < 8; i++) {
        int alt = i;
        for (int j = 0; j < 8; j++) {
            sf::RectangleShape tile;
            float x = 100 * i;
            float y = 100 * j;
            tile.setSize({100, 100});
            tile.setPosition({x, y});
            if (alt % 2 != 0) {
                tile.setFillColor(sf::Color(118, 150, 86));
            }
            else {
                tile.setFillColor(sf::Color(238, 238, 210));
            };

            board.push_back(tile);
            alt++;
        };
    };
};

void pawnRow(std::vector<ChessPiece>& pieces) {
    // Black Pawns
    for (int i = 0; i < 8; i++) {
        sf::Texture* pawnTexture = new sf::Texture("../assets/chess_pieces/black_pawn.png");
        ChessPiece new_pawn(*(pawnTexture), true, Piece_Type::Pawn, 0, 0);
        sf::Vector2f targetSize(100.0f, 100.0f);

        float X = targetSize.x / new_pawn.localSprite.getLocalBounds().size.x;
        float Y = targetSize.y / new_pawn.localSprite.getLocalBounds().size.y;

        new_pawn.localSprite.setScale({X, Y});
        X = i * 100;
        Y = 1 * 100;
        new_pawn.localSprite.setPosition({X, Y});
        
        pieces.push_back(new_pawn);
    };
    // White Pawns
    for (int i = 0; i < 8; i++) {
        sf::Texture* pawnTexture = new sf::Texture("../assets/chess_pieces/white_pawn.png");
        ChessPiece new_pawn(*(pawnTexture), true, Piece_Type::Pawn, 0, 0);
        sf::Vector2f targetSize(100.0f, 100.0f);

        float X = targetSize.x / new_pawn.localSprite.getLocalBounds().size.x;
        float Y = targetSize.y / new_pawn.localSprite.getLocalBounds().size.y;

        new_pawn.localSprite.setScale({X, Y});
        X = i * 100;
        Y = 6 * 100;
        new_pawn.localSprite.setPosition({X, Y});
        
        pieces.push_back(new_pawn);
    };
};

bool move(ChessPiece& piece, Position& desired_location) {

};

std::vector<Position> all_moves_bishop(const Position& starting_location) {
    std::vector<Position> res;
    for (int i = 1; i < 8; i++) {
        Position LeftUp(starting_location.row + i, starting_location.col - i);
        Position LeftDown(starting_location.row - i, starting_location.col - i);
        Position RightUp(starting_location.row + i, starting_location.col + i);
        Position RightDown(starting_location.row - i, starting_location.col + i);

        res.push_back(LeftUp);
        res.push_back(LeftDown);
        res.push_back(RightUp);
        res.push_back(RightDown);
    };

    return res;
};



std::vector<Position> all_moves_rook(const Position& starting_location) {
    std::vector<Position> res;
    for (int i = 1; i < 8; i++) {
        Position UpPos(starting_location.row - i, starting_location.col);
        Position DownPos(starting_location.row + i, starting_location.col);
        Position LeftPos(starting_location.row, starting_location.col - i );
        Position RightPos(starting_location.row, starting_location.col + i);

        res.push_back(UpPos);
        res.push_back(DownPos);
        res.push_back(LeftPos);
        res.push_back(RightPos);
    };

    return res;
};

std::vector<Position> all_moves_king(const Position& starting_location) {
    std::vector<Position> res;

    for (int i = -1; i < 2; i++) {
        for (int j = 1; j > -2; j--) {
            if (i == j && j == 0) {
                continue;
            };
            Position newPos(starting_location.row + i, starting_location.col + j);
            res.push_back(newPos);
        };
    };

    return res;
};

std::vector<Position> all_moves_knight(const Position& starting_location) {

};

std::vector<Position> all_moves_pawn(const Position& starting_location) {
    std::vector<Position> res;

    return res;
};
std::vector<Position> legal_moves(Piece_Type piece_type, const Position& starting_position) {
    std::vector<Position> res;
    switch(piece_type) {
        case Piece_Type::Pawn:
            all_moves_pawn(starting_position);
            break;
        case Piece_Type::King:
            all_moves_king(starting_position);
            break;
        case Piece_Type::Queen:
            all_moves_bishop(starting_position);
            all_moves_rook(starting_position);
            break;
        case Piece_Type::Bishop:
            all_moves_bishop(starting_position);
            break;
        case Piece_Type::Knight:
            break;
        case Piece_Type::Rook:
            all_moves_rook(starting_position);
            break;
        default:
            std::cerr << "A piece was not properly defined";
            break;        
    };

    return res;
};