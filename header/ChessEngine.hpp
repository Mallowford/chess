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
    bool hasMoved = false;
    Piece_Type piece = Piece_Type::Pawn;
    Position pos;
    ChessPiece(const sf::Texture& texture, bool isWhite, Piece_Type type, int row, int col) : localSprite(texture), White(isWhite), piece(type), pos(row, col) {};
};

class Engine {
    private:
        std::unordered_map<Position, ChessPiece*> boardState;
    public:
        Engine();
        ~Engine();
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;

        void start();
        void CreateBoard(std::vector<sf::RectangleShape>& board);
        void pawnRow(std::vector<ChessPiece>& board);
        std::vector<Position> legal_moves(Piece_Type type, const Position& starting_position);
        Position click_detection(sf::Vector2i);
        bool move();
};