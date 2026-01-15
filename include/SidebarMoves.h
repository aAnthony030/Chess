#pragma once

#include <vector>
#include "Struct.h"

using namespace std;
using PieceTypes::PAWN;
using PieceTypes::BISHOP;
using PieceTypes::KNIGHT;
using PieceTypes::ROOK;
using PieceTypes::QUEEN;
using PieceTypes::KING;

string ChessNotation(pair<float, float> move, enum PieceTypes type, bool& piece_eat, bool& short_castle, bool& long_castle, bool& check, bool& checkmate, bool& promotion) {
    int row = int(move.second) / 80;
    int col = int(move.first) / 80;

    char row_chr = 'a' + row;
    char col_chr = '8' - col; // parto dalla fine perchè y = 0 indica la fine della scacchiera
    char type_chr;
    switch(type) {
        case BISHOP: type_chr = 'B'; break;
        case ROOK: type_chr = 'R'; break;
        case KING: type_chr = 'K'; break;
        case QUEEN: type_chr = 'Q'; break;
        case KNIGHT: type_chr = 'N'; break;
    }

    if (check && piece_eat) {
        if (type != PAWN) {
            string chess_notation = string(1, type_chr) + string(1, row_chr) + string(1, 'x') + string(1, col_chr) + string(1, '+');
            check = false;
            piece_eat = false;
            return chess_notation;
        }
        string chess_notation = string(1, row_chr) + string(1, 'x') + string(1, col_chr) + string(1, '+');
        check = false;
        piece_eat = false;
        return chess_notation;
        
    }

    if (checkmate && piece_eat) {
        if (type != PAWN) {
            string chess_notation = string(1, type_chr) + string(1, row_chr) + string(1, 'x') + string(1, col_chr) + string(1, '#');
            checkmate = false;
            piece_eat = false;
            return chess_notation;
        }

        string chess_notation = string(1, row_chr) + string(1, 'x') + string(1, col_chr) + string(1, '#');
        checkmate = false;
        piece_eat = false;
        return chess_notation;
    }

    if (piece_eat) {
        if (type != PAWN) {
            string chess_notation = string(1, type_chr) + string(1, row_chr) + string(1, 'x') + string(1, col_chr);
            piece_eat = false;
            return chess_notation;
        }
        string chess_notation = string(1, row_chr) + string(1, 'x') + string(1, col_chr);
        piece_eat = false;
        return chess_notation;
    }


    if (short_castle) {
        string chess_notation = "O-O";
        short_castle = false;
        return chess_notation;
    }

    if (long_castle) {
        string chess_notation = "O-O-O";
        long_castle = false;
        return chess_notation;
    }

    if (checkmate) {
        if (type != PAWN) {
            string chess_notation = string(1, type_chr) + string(1, row_chr) + string(1, col_chr) + string(1, '#');
            checkmate = false;
            return chess_notation;
        }

        string chess_notation = string(1, row_chr) + string(1, col_chr) + string(1, '#');
        checkmate = false;
        return chess_notation;

    }
    
    if (check) {
        if (type != PAWN) {
            string chess_notation = string(1, type_chr) + string(1, row_chr) + string(1, col_chr) + string(1, '+');
            check = false;
            return chess_notation;
        }

        string chess_notation = string(1, row_chr) + string(1, col_chr) + string(1, '+');
        check = false;
        return chess_notation;

    }
    
    if (promotion) {
        string chess_notation = string(1, row_chr) + string(1, col_chr) + string(1, '=') + string(1, type_chr);
        return chess_notation;
    }

    if (type != PAWN) {
        string chess_notation = string(1, type_chr) + (1, row_chr) + string(1, col_chr);
        return chess_notation;
    }
    
    string chess_notation = string(1, row_chr) + string(1, col_chr);
    return chess_notation;

}

void MovesHistory(pair<float, float> move, enum PieceTypes type, vector<string>& history_moves, bool& piece_eat, bool& short_castle, bool& long_castle, bool& check, bool& checkmate, bool& promotion) {
    const int MAX_MOVES = 15; // mosse massime visualizabili
    string move_str = ChessNotation(move, type, piece_eat, short_castle, long_castle, check, checkmate, promotion);

    history_moves.push_back(move_str);
    if (history_moves.size() > MAX_MOVES) {
        history_moves.erase(history_moves.begin(), history_moves.end() - MAX_MOVES);
    }

}