#include "../header/Chess.hpp"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

enum Piece_Type {
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King
};

struct chessPiece {
    sf::Sprite sprite;
    bool White = true;
    Piece_Type piece = Pawn;
};

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "My Window");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);

    sf::Clock billyMays;

    sf::Texture texture("../assets/chess_pieces/pawn.png");
    sf::Sprite sprite(texture);
    sprite.setPosition({0.0f, 0.0f});
    sprite.scale({0.02f, 0.02f});
    std::vector<sf::Sprite> board;
    std::vector<chessPiece> pieces;

    std::cout << sprite.getScale().x << "\n";
    std::cout << sprite.getScale().y << "\n";

    sf::RectangleShape tile1({800.0f, 600.0f});
    tile1.setFillColor(sf::Color(118, 150, 86));

    sf::RectangleShape tile2({400.0f, 600.0f});
    tile2.setFillColor(sf::Color(238, 238, 210));
    tile2.move({400, 0});

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

        window.draw(tile1);
        window.draw(tile2);
        window.draw(sprite);

        window.display();        
    };

    std::cout << "Program Ended\n";
    return 0;
};