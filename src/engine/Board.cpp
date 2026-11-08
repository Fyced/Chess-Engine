#include "engine/Board.h"
#include <iostream>
#include <cctype>

constexpr int NUM_SQUARES = 64;

Board::Board(){
    loadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

Board:: Board(const string& fen){
    loadFEN(fen);
}


static char pieceToChar(Piece p) {
    char c = '.';
    switch (p.type) {
        case PieceType::Pawn:   c = 'p'; break;
        case PieceType::Knight: c = 'n'; break;
        case PieceType::Bishop: c = 'b'; break;
        case PieceType::Rook:   c = 'r'; break;
        case PieceType::Queen:  c = 'q'; break;
        case PieceType::King:   c = 'k'; break;
        case PieceType::None:   return '.';
    }
    return p.color == Color::White ? static_cast<char>(std::toupper(c)) : c;
}

static Piece charToPiece(char c) {
    Piece res;
    switch (std::tolower(c)) {
        case 'p': res.type = PieceType::Pawn;   break;
        case 'n': res.type = PieceType::Knight; break;
        case 'b': res.type = PieceType::Bishop; break;
        case 'r': res.type = PieceType::Rook;   break;
        case 'q': res.type = PieceType::Queen;  break;
        case 'k': res.type = PieceType::King;   break;
    }
    res.color = std::islower(c) ? Color::Black : Color::White;
    return res;
}

static Color charToColor(char c) {
    return (c == 'w') ? Color::White : Color::Black;
}

void Board::loadFEN(const std::string& fen) {
    for (Piece& p : board) p = Piece{};
    castleWK = castleWQ = castleBK = castleBQ = false;
    enPassant = -1;
    halfmoveClock = 0;
    fullMoveNumber = 0;

    int sq = 56;
    int blank = 0;

    for (size_t i = 0; i < fen.length(); i++) {
        char c = fen[i];
        if (c == ' ') { blank++; continue; }

        if (blank == 0) {
            if (c == '/')             sq -= 16;
            else if (std::isdigit(c)) sq += c - '0';
            else { board[sq] = charToPiece(c); sq++; }
        }
        else if (blank == 1) {
            turn = charToColor(c);
        }
        else if (blank == 2) {
            switch (c) {
                case 'K': castleWK = true; break;
                case 'Q': castleWQ = true; break;
                case 'k': castleBK = true; break;
                case 'q': castleBQ = true; break;
            }
        }
        else if (blank == 3) {
            if (c >= 'a' && c <= 'h')      enPassant = c - 'a';
            else if (c >= '1' && c <= '8') enPassant += (c - '1') * 8;
        }
        else if (blank == 4) {
            halfmoveClock = halfmoveClock * 10 + (c - '0');
        }
        else if (blank == 5) {
            fullMoveNumber = fullMoveNumber * 10 + (c - '0');
        }
    }
}

void Board::print() const {
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            std::cout << pieceToChar(board[rank * 8 + file]) << ' ';
        }
        std::cout << '\n';
    }
}
