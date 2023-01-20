//
// Created by david on 16.02.2021.
//

#include <iostream>
#include "board.h"

Gamestate::Gamestate(enum color side_to_move, uint8_t rights, uint8_t en_passant_target,
                     uint8_t reversible_moves) : state(0) {
    state |= static_cast<uint32_t>(side_to_move)<<static_cast<uint32_t>(state_slicing::color);
    state |= static_cast<uint32_t>(rights)<<static_cast<uint32_t>(state_slicing::castling);
    state |= static_cast<uint32_t>(en_passant_target)<<static_cast<uint32_t>(state_slicing::en_passant);
    state |= static_cast<uint32_t>(reversible_moves)<<static_cast<uint32_t>(state_slicing::counter);
}

enum color Gamestate::side_to_move() const noexcept {
    return static_cast<enum color>(
            static_cast<uint8_t>((state>>static_cast<uint32_t>(Gamestate::state_slicing::color)))
            & static_cast<uint8_t>(color::white)
            );
}

uint8_t Gamestate::reversible_moves() const noexcept {
    return static_cast<uint8_t>((state>>static_cast<uint32_t>(Gamestate::state_slicing::counter)));
}

uint8_t Gamestate::en_passant_target() const noexcept {
    return static_cast<uint8_t>((state>>static_cast<uint32_t>(Gamestate::state_slicing::en_passant)));
}

uint8_t Gamestate::castling_rights() const noexcept {
    return static_cast<uint8_t>((state>>static_cast<uint32_t>(Gamestate::state_slicing::castling)));
}

uint32_t Gamestate::gamestate() const noexcept {
    return state;
}

Board::Board(std::string fen) : board() {
    // Parsing FEN notation:
    // https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation

    auto pos = 0;

    auto x = 0;
    auto y = 0;

    for(; pos < fen.length() && fen[pos] != ' '; pos+=1){
        char __dbg = fen[pos];
        // parse position of FEN string
        switch (fen[pos]) {
            case '/':
                y += 1;
                break;
            case '8':
            case '7':
            case '6':
            case '5':
            case '4':
            case '3':
            case '2':
            case '1':
                x += fen[pos]-'0';
                break;
            default:
                board[y] |= (static_cast<uint32_t>(Piece::from_fen(fen[pos]))<<(4*x));
                x += 1;
        }
    }

    // parse metadata of FEN string

    // color on turn
    pos += 1; // step over initial space
    enum color c = (tolower(fen[pos]) == 'w' ? color::white : color::black);
    pos += 1;

    // castling
    pos += 1; // step over initial space
    uint8_t castl = 0;
    for(;fen[pos] != ' '; pos+=1){
        switch (fen[pos]) {
            case 'K':
                castl |= static_cast<uint8_t>(castling::WHITE_KING);
                break;
            case 'k':
                castl |= static_cast<uint8_t>(castling::BLACK_KING);
                break;
            case 'Q':
                castl |= static_cast<uint8_t>(castling::WHITE_QUEEN);
                break;
            case 'q':
                castl |= static_cast<uint8_t>(castling::BLACK_QUEEN);
                break;
        }
    }

    // en passant
    pos += 1; // step over initial space
    uint8_t en_passant = 0xff;
    if(fen[pos] != '-'){
        en_passant = (fen[pos]-'a')+8*fen[pos+1]-'1';
        pos += 1;
    }
    pos += 1;

    // half turns
    pos += 1; // step over initial space
    uint8_t ht = stoi(fen.substr(pos));

    // turn counter
    // we don't know the length, so we have to do it properly
    counter = stoi(fen.substr(fen.find(' ', pos+1)));

    state = Gamestate(c, castl, en_passant, ht);
}

// Initialize default board state using FEN notation
Board::Board() : Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1") {
}

Piece Board::at(uint8_t x, uint8_t y) const noexcept {
    return Piece(from(x, y));
}

std::array<uint32_t, 10> Board::gamestate() {
    std::array<uint32_t, 10> result;
    for(auto i=0; i<8; i+=1)
        result[i] = board[i];
    result[8] = state.gamestate();
    result[9] = counter;
    return result;
}

enum color Board::side_to_move() const noexcept {
    return state.side_to_move();
}

uint8_t Board::reversible_moves() const noexcept {
    return state.reversible_moves();
}

uint8_t Board::en_passant_target() const noexcept {
    return state.en_passant_target();
}

uint8_t Board::castling_rights() const noexcept {
    return state.castling_rights();
}

uint8_t Board::moves() const noexcept {
    return counter;
}

void Board::move(uint8_t from_x, uint8_t from_y, uint8_t to_x, uint8_t to_y, Gamestate new_state) noexcept {
    auto p = from(from_x, from_y);
    auto t = from(to_x, to_y);
    board[to_y] ^= (static_cast<uint32_t>(p^t))<<(4*to_x);
    board[from_y] ^= static_cast<uint32_t>(p)<<(4*from_x);

    state = new_state;

    counter += 1;
}

uint8_t Board::from(uint8_t x, uint8_t y) const noexcept{
    return static_cast<uint8_t>(board[y]>>(4*x));
}
