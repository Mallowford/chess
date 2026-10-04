#include "../header/ChessEngine.hpp"

std::vector<Position> Engine::all_moves_bishop(const Position& starting_location) {
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



std::vector<Position> Engine::all_moves_rook(const Position& starting_location) {
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

std::vector<Position> Engine::all_moves_king(const Position& starting_location) {
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
std::vector<Position> Engine::all_moves_knight(const Position& starting_location) {
    std::vector<Position> res;

    std::vector<Position> offset = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

    for (int i = 0; i < offset.size(); i++) {
        Position newMove(starting_location.row + offset.at(i).row, starting_location.col + offset.at(i).col);
        res.push_back(newMove);
    };


    return res;
};
std::vector<Position> Engine::all_moves_pawn(const Position& starting_location) {
    std::vector<Position> res;
    
    // for (int i = ) {

    // };

    return res;
};
std::vector<Position> Engine::legal_moves(Piece_Type piece_type, const Position& starting_position) {
    std::vector<Position> res;
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

Position Engine::click_detection(sf::Vector2i mousePos) {

    Position affectedPiece(mousePos.y/100, mousePos.x/100);

    if (affectedPiece.col == 8) {
        affectedPiece.col = 7;
    };
    if (affectedPiece.row == 8) {
        affectedPiece.row = 7;
    };

    if (boardState.at(affectedPiece.row).at(affectedPiece.col).piece != Piece_Type::EMPTY) {
        lastClickLocation.col = affectedPiece.col;
        lastClickLocation.row = affectedPiece.row;
    };

    return affectedPiece;
};

void Engine::CreateBoard() {
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

            this->boardSprites.push_back(tile);
            alt++;
        };
    };
};

void Engine::pawnRow() {
    for (int i = 0; i < 8; i++) {
        std::vector<ChessPiece> empty;
        for (int j = 0; j < 8; j++) {
            ChessPiece em(false, Piece_Type::EMPTY);
            empty.push_back(em);
        };
        this->boardState.push_back(empty);
    };
    // Black Pawns

    for (int i = 0; i < 8; i++) {
        sf::Texture* pawnTexture = new sf::Texture("../assets/chess_pieces/black_pawn.png");
        ChessPiece new_pawn(*(pawnTexture), true, Piece_Type::Pawn);
        float standard_size = WINDOW_SIZE / 8.0f;
        sf::Vector2f targetSize(standard_size, standard_size);

        float X = targetSize.x / new_pawn.localSprite->getLocalBounds().size.x;
        float Y = targetSize.y / new_pawn.localSprite->getLocalBounds().size.y;

        new_pawn.localSprite->setScale({X, Y});
        X = i * (standard_size);
        Y = 1 * (standard_size);
        new_pawn.localSprite->setPosition({X, Y});
        this->boardState.at(1).at(i) = new_pawn;
    };
    // White Pawns
    for (int i = 0; i < 8; i++) {
        sf::Texture* pawnTexture = new sf::Texture("../assets/chess_pieces/white_pawn.png");
        ChessPiece new_pawn(*(pawnTexture), true, Piece_Type::Pawn);
        float standard_size = WINDOW_SIZE / 8.0f;
        sf::Vector2f targetSize(standard_size, standard_size);

        float X = targetSize.x / new_pawn.localSprite->getLocalBounds().size.x;
        float Y = targetSize.y / new_pawn.localSprite->getLocalBounds().size.y;

        new_pawn.localSprite->setScale({X, Y});
        X = i * standard_size;
        Y = 6 * standard_size;
        new_pawn.localSprite->setPosition({X, Y});
        
        this->boardState.at(6).at(i) = new_pawn;
    };
};

void Engine::start() {
    CreateBoard();
    pawnRow();
};

void Engine::draw(sf::RenderWindow& window) {
    // Draw Board
    for (int i = 0; i < this->boardSprites.size(); i++) {
        window.draw(boardSprites.at(i));
    };

    // Draw Pieces
    for (int i = 0; i < this->boardState.size(); i++) {
        for (int j = 0; j < this->boardState.at(i).size(); j++) {
            if (this->boardState.at(i).at(j).piece == Piece_Type::EMPTY) {
                continue;
            };
            window.draw(*(this->boardState.at(i).at(j)).localSprite);
        };
    };

    // Draw Spots Where Piece Can Move
    

};

Engine::Engine() : lastClickLocation(-1, -1) {
};
Engine::~Engine() {};