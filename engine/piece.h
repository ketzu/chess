//
// Created by david on 16.02.2021.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <cstdint>

enum class shape {
    empty = 0,
    pawn = 1,
    bishop = 2,
    knight = 3,
    rook = 4,
    queen = 5,
    king = 6
};

enum class color {
    black = 0,
    white = 8
};

class Piece {
private:
    uint8_t type;
public:
    explicit Piece(uint8_t type);
    explicit Piece(shape s, color c);

    // static to prevent confusion with uint8_t constructor
    // also more a translation table associated with Piece
    static uint8_t from_fen(char c);

    [[nodiscard]] shape shape() const noexcept;
    [[nodiscard]] color color() const noexcept;

    [[nodiscard]] uint8_t internal() const noexcept;

    [[nodiscard]] char fen() const noexcept;
};

#endif //CHESS_PIECE_H
