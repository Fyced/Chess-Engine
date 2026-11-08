#pragma once

enum Color {White, Black};
enum PieceType {None, Rook, Knight, Bishop, Queen, King, Pawn};

struct Piece{
    Color color = White;
    PieceType type = None;

    bool isEmpty() const {return type==None;}
};

using Square = int;

struct Move{
    Square from;
    Square to;

    PieceType promotion = None;

    bool capture = false;
    bool isCastle = false;
    bool isEnPassant = false;
};