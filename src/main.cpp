#include "../header/ChessEngine.hpp"

int main() {
    Engine engine;

    sf::RenderWindow window(sf::VideoMode({WINDOW_SIZE, WINDOW_SIZE}), "Chess", sf::State::Windowed, {sf::Style::Titlebar, sf::Style::Close});
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);


    sf::Clock billyMays;

    std::vector<ChessPiece> pieces;

    engine.start();
    // CreateBoard();
    // pawnRow(pieces);
    // Position test_location(5, 5);

    // std::vector<Position> printMoves = legal_moves(Piece_Type::Knight, test_location);

    // for (auto& view : printMoves) {
    //     std::cout << "Col: " << view.col << "\tRow: " << view.row << "\n";  
    // };

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            };
            if (event->is<sf::Event::MouseButtonPressed>()) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    Position clickLocation = engine.click_detection(sf::Mouse::getPosition(window));
                    std::cout << "Row: " << clickLocation.row << "\tCol: " << clickLocation.col << "\n";
                    // Pass Click Location into a check, see if there's a piece there, if so calculate moves and store it
                    // Tell engine to store "last active click"
                    // If next click is a possible move for that last active position, then move piece
                };
            };
        };
        if (!window.hasFocus()) { // Lost Focus
            if (billyMays.getElapsedTime().asSeconds() > 1) {
                std::cout << "Not focused!\n";
                billyMays.restart();
            };
        };



        window.clear(sf::Color::Black);

        engine.draw(window);

        window.display();        
    };

    std::cout << "Program Ended\n";
    return 0;
};



bool move(ChessPiece& piece, Position desired_location) {
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