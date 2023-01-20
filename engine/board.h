//
// Created by david on 16.02.2021.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H


#include <array>
#include "piece.h"

enum class castling {
    NONE = 0,
    WHITE_KING = 1,
    WHITE_QUEEN = 2,
    BLACK_KING = 4,
    BLACK_QUEEN = 8
};

class Gamestate {
private:
    // to encode everything in a single uint32 we shift it around
    // the distance for the parts is encoded in this enum
    enum class state_slicing{
        color = 0,
        castling = 8,
        en_passant = 16,
        counter = 24
    };
    uint32_t state;
public:
    Gamestate() = default;
    Gamestate(Gamestate&) = default;
    Gamestate(enum color side_to_move,uint8_t rights, uint8_t en_passant_target, uint8_t reversible_moves);

    [[nodiscard]] uint32_t gamestate() const noexcept;

    [[nodiscard]] enum color side_to_move() const noexcept;
    [[nodiscard]] uint8_t reversible_moves() const noexcept;
    [[nodiscard]] uint8_t en_passant_target() const noexcept;
    [[nodiscard]] uint8_t castling_rights() const noexcept;
};

class Board {
private:
    std::array<uint32_t, 8> board;
    Gamestate state;
    uint32_t counter;

    inline uint8_t from(uint8_t x, uint8_t y) const noexcept;
public:
    explicit Board();
    explicit Board(std::string fen);

    void move(uint8_t from_x, uint8_t from_y, uint8_t to_x, uint8_t to_y, Gamestate new_state) noexcept;

    [[nodiscard]] Piece at(uint8_t x, uint8_t y) const noexcept;
    [[nodiscard]] std::array<uint32_t,10> gamestate();

    [[nodiscard]] enum color side_to_move() const noexcept;
    [[nodiscard]] uint8_t reversible_moves() const noexcept;
    [[nodiscard]] uint8_t en_passant_target() const noexcept;
    [[nodiscard]] uint8_t castling_rights() const noexcept;
    [[nodiscard]] uint8_t moves() const noexcept;
};


#endif //CHESS_BOARD_H
