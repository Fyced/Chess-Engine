#pragma once
#include <string>
#include <vector>
#include "engine/Types.h"

using namespace std;

class Board{
    public:
        Board();
        Board(const string& fen);

        void loadFEN(const string& fen);
        void makeMove(const Move& m);
        void unmakeMove(const Move& move);
        void print() const;

        Piece board[64];

        Color turn = Color::White;
        bool castleWK = false, castleWQ = false, castleBK = false, castleBQ = false;

        Square enPassant = -1;

        int halfmoveClock = 0;
        int fullMoveNumber = 1;


    private:
        struct UndoInfo{
            Piece captured; 
            bool castleWK, castleWQ, castleBK, castleBQ; 
            Square enPassant;
            int halfmoveClock = 0;
        };
        vector<UndoInfo> history;
};