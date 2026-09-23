#include "../header/Chess.hpp"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#define WINDOW_SIZE 800

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
std::vector<Position> legal_moves(Piece_Type type, const Position& starting_position);

int main() {
    sf::RenderWindow window(sf::VideoMode({WINDOW_SIZE, WINDOW_SIZE}), "Chess", sf::State::Windowed, {sf::Style::Titlebar, sf::Style::Close});
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);

    sf::Clock billyMays;

    std::vector<sf::RectangleShape> map;
    std::vector<ChessPiece> pieces;

    CreateBoard(map);
    pawnRow(pieces);
    Position test_location(5, 5);

    std::vector<Position> printMoves = legal_moves(Piece_Type::Knight, test_location);

    for (auto& view : printMoves) {
        std::cout << "Col: " << view.col << "\tRow: " << view.row << "\n";  
    };

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
        float standard_size = WINDOW_SIZE / 8.0f;
        sf::Vector2f targetSize(standard_size, standard_size);

        float X = targetSize.x / new_pawn.localSprite.getLocalBounds().size.x;
        float Y = targetSize.y / new_pawn.localSprite.getLocalBounds().size.y;

        new_pawn.localSprite.setScale({X, Y});
        X = i * (standard_size);
        Y = 1 * (standard_size);
        new_pawn.localSprite.setPosition({X, Y});
        
        pieces.push_back(new_pawn);
    };
    // White Pawns
    for (int i = 0; i < 8; i++) {
        sf::Texture* pawnTexture = new sf::Texture("../assets/chess_pieces/white_pawn.png");
        ChessPiece new_pawn(*(pawnTexture), true, Piece_Type::Pawn, 0, 0);
        float standard_size = WINDOW_SIZE / 8.0f;
        sf::Vector2f targetSize(standard_size, standard_size);

        float X = targetSize.x / new_pawn.localSprite.getLocalBounds().size.x;
        float Y = targetSize.y / new_pawn.localSprite.getLocalBounds().size.y;

        new_pawn.localSprite.setScale({X, Y});
        X = i * standard_size;
        Y = 6 * standard_size;
        new_pawn.localSprite.setPosition({X, Y});
        
        pieces.push_back(new_pawn);
    };
};

bool move(ChessPiece& piece, Position& desired_location) {
    return false;
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
    std::vector<Position> res;

    std::vector<Position> offset = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

    for (int i = 0; i < offset.size(); i++) {
        Position newMove(starting_location.row + offset.at(i).row, starting_location.col + offset.at(i).col);
        res.push_back(newMove);
    };


    return res;
};

std::vector<Position> all_moves_pawn(const Position& starting_location) {
    std::vector<Position> res;
    
    // for (int i = ) {

    // };

    return res;
};
std::vector<Position> legal_moves(Piece_Type piece_type, const Position& starting_position) {
    std::vector<Position> res;
    // std::vector<Position> to_add;
    switch(piece_type) {
        case Piece_Type::Pawn:
            res = all_moves_pawn(starting_position);
            break;
        case Piece_Type::King:
            res = all_moves_king(starting_position);
            break;
        case Piece_Type::Knight:
            res = all_moves_knight(starting_position);
            break;
        case Piece_Type::Queen:
            [[fallthrough]];
        case Piece_Type::Bishop:
            res = all_moves_bishop(starting_position);
            if (piece_type == Piece_Type::Bishop) {
                break;
            };
            [[fallthrough]];
        case Piece_Type::Rook:
            {
            auto rook_moves = all_moves_rook(starting_position);
            res.insert(res.end(), rook_moves.begin(), rook_moves.end());
            };
            break;
        default:
            std::cerr << "A piece was not properly defined";
            break;
    };

    // Remove out of bound cases
    auto it = res.begin();

    while (it != res.end()) {
        if (it->col < 0 || it->row < 0 || it->col > 7 || it->row > 7) {
          it = res.erase(it);
        }
        else {
            it++;
        };
    };

    // Determine if something is blocking the path
    // WIP, Requires Board Knowledge

    // Determine if moving will cause check/checkmate

    // If in Check, remove all moves that do not prevent check

    // En passante 

    return res;
};