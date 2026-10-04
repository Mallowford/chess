#pragma once
#define WINDOW_SIZE 800
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>

enum class Piece_Type {
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King,
    EMPTY
};

struct Position {
    int row;
    int col;
    Position(int row, int col) : row(row), col(col) {};
};

struct ChessPiece {
    std::optional<sf::Sprite> localSprite;
    bool White = true;
    bool hasMoved = false;
    Piece_Type piece = Piece_Type::Pawn;
    ChessPiece(const sf::Texture& texture, bool isWhite, Piece_Type type) : localSprite(texture), White(isWhite), piece(type) {};
    ChessPiece(bool isWhite, Piece_Type type) : White(isWhite), piece(type) {};
};

class Engine {
    private:
        std::vector<std::vector<ChessPiece>> boardState;
        std::vector<sf::RectangleShape> boardSprites;
        Position lastClickLocation;
    public:
        Engine();
        ~Engine();
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;

        void start();
        std::vector<Position> legal_moves(Piece_Type type, const Position& starting_position);
        Position click_detection(sf::Vector2i);
        bool move();
        void draw(sf::RenderWindow& window);
    private:
        void CreateBoard();
        void pawnRow();
        std::vector<Position> all_moves_knight(const Position& starting_location);
        std::vector<Position> all_moves_pawn(const Position& starting_location);
        std::vector<Position> all_moves_king(const Position& starting_location);
        std::vector<Position> all_moves_rook(const Position& starting_location);
        std::vector<Position> all_moves_bishop(const Position& starting_location);
};
