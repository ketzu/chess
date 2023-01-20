//
// Created by david on 16.02.2021.
//

#include "Move.h"

std::vector<uint8_t> attacked(const Board &b) {
    return std::vector<uint8_t>();
}

std::vector<Move> generate(const Board &b) {
    auto under_attack = attacked(b);
    return std::vector<Move>();
}

void MoveGenerator::compute_attacked() {

}

MoveGenerator::MoveGenerator(Board &b) : board(b) {
    compute_attacked();

    for (auto y = 0; y < 8; y += 1) {
        for (auto x = 0; x < 8; x += 1) {
            auto p = b.at(x, y);
            switch (p.shape()) {
                case shape::pawn:
                    add_pawnmoves(x, y);
                    break;
                case shape::bishop:
                    add_bishopmoves(x, y);
                    break;
                case shape::knight:
                    add_knightmoves(x, y);
                    break;
                case shape::rook:
                    add_rookmoves(x, y);
                    break;
                case shape::queen:
                    add_queenmoves(x, y);
                    break;
                case shape::king:
                    add_kingmoves(x, y);
                    add_castling(x, y);
                    break;
            }
        }
    }
}

std::vector<uint8_t> MoveGenerator::attacked() {
    return attack_targets;
}

void MoveGenerator::add_castling(uint8_t x, uint8_t y) {

}

void MoveGenerator::add_pawnmoves(uint8_t x, uint8_t y) {

}

void MoveGenerator::add_bishopmoves(uint8_t x, uint8_t y) {

}

void MoveGenerator::add_knightmoves(uint8_t x, uint8_t y) {

}

void MoveGenerator::add_rookmoves(uint8_t x, uint8_t y) {

}

void MoveGenerator::add_queenmoves(uint8_t x, uint8_t y) {

}

void MoveGenerator::add_kingmoves(uint8_t x, uint8_t y) {

}

std::vector<Move> MoveGenerator::possible_moves() {
    return moves;
}
