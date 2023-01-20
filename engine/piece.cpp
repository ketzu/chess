//
// Created by david on 16.02.2021.
//

#include <cctype>
#include <iostream>
#include "piece.h"

Piece::Piece(uint8_t type) : type(type) {

}

Piece::Piece(enum shape s, enum color c)  : type(static_cast<uint8_t>(s)|static_cast<uint8_t>(c)) {

}

uint8_t Piece::from_fen(char fen) {
    // Parsing FEN notation:
    // https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
    enum color c;
    enum shape s;
    if('A' < fen && fen < 'Z'){
        c = color::white;
    }else{
        c = color::black;
    }
    switch (tolower(fen)) {
        case 'p':
            s = shape::pawn;
            break;
        case 'b':
            s = shape::bishop;
            break;
        case 'n':
            s = shape::knight;
            break;
        case 'r':
            s = shape::rook;
            break;
        case 'q':
            s = shape::queen;
            break;
        case 'k':
            s = shape::king;
            break;
        default:
            std::cerr << "Failed to create a correct piece from: " << fen << "\n";
    }
    return static_cast<uint8_t>(s)|static_cast<uint8_t>(c);
}

enum shape Piece::shape() const noexcept {
    return static_cast<enum shape>(type & 0b0111);
}

enum color Piece::color() const noexcept {
    return static_cast<enum color>(type & 0b1000);
}

uint8_t Piece::internal() const noexcept {
    return type;
}

char Piece::fen() const noexcept {
    char fig = ' ';
    switch (shape()) {
        case shape::king: fig = 'K'; break;
        case shape::queen: fig = 'Q'; break;
        case shape::rook: fig = 'R'; break;
        case shape::knight: fig = 'N'; break;
        case shape::bishop: fig = 'B'; break;
        case shape::pawn: fig = 'P'; break;
    }
    if(color() == color::black)
        return tolower(fig);
    return fig;
}
