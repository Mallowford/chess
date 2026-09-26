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

struct ChessPiece {
    sf::Sprite localSprite;
    bool White = true;
    Piece_Type piece = Piece_Type::Pawn;
    bool hasMoved = false;
    ChessPiece(const sf::Texture& texture, bool isWhite, Piece_Type type) : localSprite(texture), White(isWhite), piece(type) {};
};

void CreateBoard(std::vector<sf::RectangleShape>& board);
void pawnRow(std::vector<ChessPiece>& board);

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
        ChessPiece new_pawn(*(pawnTexture), true, Piece_Type::Pawn);
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
        ChessPiece new_pawn(*(pawnTexture), true, Piece_Type::Pawn);
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