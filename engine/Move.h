//
// Created by david on 16.02.2021.
//

#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H


#include <vector>
#include "piece.h"
#include "board.h"

struct Move {
    uint8_t from_x;
    uint8_t from_y;
    uint8_t to_x;
    uint8_t to_y;
    enum shape promotion_to;
    enum castling castle;
    Gamestate new_state;
};

class MoveGenerator {
private:
    std::vector<uint8_t> attack_targets;
    std::vector<Move> moves;
    Board& board;

    void compute_attacked();

public:
    explicit MoveGenerator(Board& b);

    std::vector<uint8_t> attacked();

    void add_castling(uint8_t x, uint8_t y);
    void add_pawnmoves(uint8_t x, uint8_t y);
    void add_bishopmoves(uint8_t x, uint8_t y);
    void add_knightmoves(uint8_t x, uint8_t y);
    void add_rookmoves(uint8_t x, uint8_t y);
    void add_queenmoves(uint8_t x, uint8_t y);
    void add_kingmoves(uint8_t x, uint8_t y);

    std::vector<Move> possible_moves();
};

#endif //CHESS_MOVE_H
