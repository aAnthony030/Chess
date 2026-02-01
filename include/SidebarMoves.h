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

string ChessNotation(pair<float, float> move, enum PieceTypes type, bool& piece_eat, bool& short_castle, bool& long_castle, 
bool& check, bool& checkmate, bool promotion, char prom_row_chr, char prom_col_chr, bool whiteTurn, char promotionPieceType_chr) {    
    int row = int(move.first) / 80;
    int col = int(move.second) / 80;

    char row_chr = 'a' + row;
    char col_chr = '8' - col; // i start from the end because y = 0 indicate the finish of the chessboard
    char type_chr;
    string turn = whiteTurn ? "BLACK: " : "WHITE: ";

    switch(type) {
        case PAWN: type_chr = '\0'; break;
        case BISHOP: type_chr = 'B'; break;
        case ROOK: type_chr = 'R'; break;
        case QUEEN: type_chr = 'Q'; break;
        case KING: type_chr = 'K'; break;
        case KNIGHT: type_chr = 'N'; break;
        default: type_chr = '\0'; break;
    }
     

    if (promotion && piece_eat) {
        string chess_notation = turn +string(1, prom_row_chr) + string(1, 'x') + string(1, prom_col_chr) + "=" + string(1, promotionPieceType_chr);
        return chess_notation;
    }
    else if (promotion && piece_eat && check) {
        string chess_notation = turn + string(1, prom_row_chr) + string(1, 'x') + string(1, prom_col_chr) + "=" + string(1, promotionPieceType_chr) + string(1, '+');
        return chess_notation;
    }
    else if (promotion && piece_eat && checkmate) {
        string chess_notation = turn + string(1, prom_row_chr) + string(1, 'x') + string(1, prom_col_chr) + "=" + string(1, promotionPieceType_chr) + string(1, '#');
        return chess_notation;
    }
    else if (promotion) {
        string chess_notation = turn + string(1, prom_row_chr) + string(1, prom_col_chr) + "=" + string(1, promotionPieceType_chr);
        return chess_notation;
    }
    

    if (check && piece_eat) {
        if (type != PAWN) {
            string chess_notation = turn + string(1, type_chr) + string(1, 'x') + string(1, row_chr) + string(1, col_chr) + string(1, '+');
            check = false;
            piece_eat = false;
            return chess_notation;
        }
        string chess_notation = turn + string(1, 'x') + string(1, row_chr)  + string(1, col_chr) + string(1, '+');
        check = false;
        piece_eat = false;
        return chess_notation;
        
    }

    if (checkmate && piece_eat) {
        if (type != PAWN) {
            string chess_notation = turn + string(1, type_chr) + string(1, 'x') + string(1, row_chr) + string(1, col_chr) + string(1, '#');
            checkmate = false;
            piece_eat = false;
            return chess_notation;
        }

        string chess_notation = turn + string(1, 'x') + string(1, row_chr) + string(1, col_chr) + string(1, '#');
        checkmate = false;
        piece_eat = false;
        return chess_notation;
    }

    if (piece_eat) {
        if (type != PAWN) {
            string chess_notation = turn + string(1, type_chr) + string(1, 'x') + string(1, row_chr) + string(1, col_chr);
            piece_eat = false;
            return chess_notation;
        }
        string chess_notation = turn + string(1, 'x') + string(1, row_chr) + string(1, col_chr);
        piece_eat = false;
        return chess_notation;
    }

    if (short_castle && checkmate) {
        string chess_notation = turn + "O-O#";
        short_castle = false;
        return chess_notation;
    }
    else if(short_castle &&  check) {
        string chess_notation = turn + "O-O+";
        short_castle = false;
        return chess_notation;
    }
    else if (short_castle) {
        string chess_notation = turn + "O-O";
        short_castle = false;
        return chess_notation;
    }


    if (long_castle && checkmate) {
        string chess_notation = turn + "O-O-O#";
        long_castle = false;
        return chess_notation;
    }
    else if(long_castle &&  check) {
        string chess_notation = turn + "O-O-O+";
        long_castle = false;
        return chess_notation;
    }
    else if (long_castle) {
        string chess_notation = turn + "O-O-O";
        long_castle = false;
        return chess_notation;
    }


    if (checkmate) {
        if (type != PAWN) {
            string chess_notation = turn + string(1, type_chr) + string(1, row_chr) + string(1, col_chr) + string(1, '#');
            checkmate = false;
            return chess_notation;
        }

        string chess_notation = turn + string(1, row_chr) + string(1, col_chr) + string(1, '#');
        checkmate = false;
        return chess_notation;

    }
    
    if (check) {
        if (type != PAWN) {
            string chess_notation = turn + string(1, type_chr) + string(1, row_chr) + string(1, col_chr) + string(1, '+');
            check = false;
            return chess_notation;
        }

        string chess_notation = turn + string(1, row_chr) + string(1, col_chr) + string(1, '+');
        check = false;
        return chess_notation;

    }

    if (type != PAWN) {
        string chess_notation = turn + string(1, type_chr) + string(1, row_chr) + string(1, col_chr);
        return chess_notation;
    }
    
    string chess_notation = turn + string(1, row_chr) + string(1, col_chr);
    return chess_notation;

}

void MovesHistory(pair<float, float> move, enum PieceTypes type, vector<string>& history_moves, bool& piece_eat, 
bool& short_castle, bool& long_castle, bool& check, bool& checkmate, bool promotion, char row_chr, char col_chr, 
bool whiteTurn, enum PieceTypes& promotionPieceType) {
    
    const int MAX_MOVES = 15; // max moves viewable
    char promotionPieceType_chr = 'P';
    if (promotion) {

        switch(promotionPieceType) {
            case PAWN: promotionPieceType_chr = '\0'; break;
            case BISHOP: promotionPieceType_chr = 'B'; break;
            case ROOK: promotionPieceType_chr = 'R'; break;
            case QUEEN: promotionPieceType_chr = 'Q'; break;
            case KING: promotionPieceType_chr = 'K'; break;
            case KNIGHT: promotionPieceType_chr = 'N'; break;
            default: promotionPieceType_chr = '\0'; break;
        }

    }
    
    string move_str = ChessNotation(move, type, piece_eat, short_castle, long_castle, check, checkmate, 
                      promotion, row_chr, col_chr, whiteTurn, promotionPieceType_chr);

    history_moves.push_back(move_str);
    if (history_moves.size() > MAX_MOVES) {
        history_moves.erase(history_moves.begin(), history_moves.end() - MAX_MOVES);
    }

}