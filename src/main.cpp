#include "../header/Chess.hpp"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

bool debounce();

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "My Window");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);

    sf::Clock billyMays;

    sf::Texture texture("../assets/chess_pieces/pawn.png");
    sf::Sprite sprite(texture);

    sprite.scale({0.02f, 0.02f});


    std::cout << sprite.getScale().x << "\n";
    std::cout << sprite.getScale().y << "\n";

    sf::RectangleShape board({120.0f, 50.0f});

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

        window.draw(sprite);
        window.draw(board);

        window.display();        
    };

    std::cout << "Program Ended\n";
    return 0;
};