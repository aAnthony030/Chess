#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <utility>

using PieceTypes::PAWN;
using PieceTypes::ROOK;
using PieceTypes::KING;

template <typename T, typename U>

//TODO: dare nomi più chiari (singoloPiece, pezzo che fa doppio movimento) (enemy_pieces, pezzo che può mangiare il prossimo turno)
bool en_passant(T singoloPiece, U& enemy_pieces, pair<float,float> move) {

    int dir = singoloPiece.isWhite ? -80 : 80;

    for (int i = 0; i < enemy_pieces.size(); i++) {
        
        if (enemy_pieces[i].type != PAWN || enemy_pieces[i].isWhite == singoloPiece.isWhite || !enemy_pieces[i].vulnerable_enPassant) continue;

            //controllo se è valido l'en passant
            if (enemy_pieces[i].vulnerable_enPassant &&
            enemy_pieces[i].position.y == singoloPiece.position.y &&
            abs(enemy_pieces[i].position.x - singoloPiece.position.x) == 80 &&
            move.first == enemy_pieces[i].position.x &&
            move.second == singoloPiece.position.y + dir) {

                return true;

            }

    }

    return false;

}


template <typename T, typename U>
bool castling(T king, U& pieces, bool short_castling) {
    const int cellsize = 80;
    int index_rook = -1;
    int rook_x = -1;
    if (!king.first_move) return false;
    
    if (short_castling) {
        rook_x = 560;
    }
    else {
        rook_x = 0;
    }

    for (int i = 0; i < pieces.size(); i++) {
        if (pieces[i].type == ROOK && pieces[i].isWhite == king.isWhite &&
        pieces[i].position.x == rook_x) {
            index_rook = i;
            break;
        }

    }

    if (index_rook == -1) {
        return false;
    }

    if (!pieces[index_rook].first_move) return false;

    if (short_castling) {

        for (int i = 0; i < pieces.size(); i++) {
            if (pieces[i].position.x == 400 && pieces[i].position.y == king.position.y || 
            pieces[i].position.x == 480 && pieces[i].position.y == king.position.y) {
                return false;
            }

        }

    }

    else {
        for (int i = 0; i < pieces.size(); i++) {
            if (pieces[i].position.x == 80 && pieces[i].position.y == king.position.y || 
            pieces[i].position.x == 160 && pieces[i].position.y == king.position.y || 
            pieces[i].position.x == 240 && pieces[i].position.y == king.position.y) {
                return false;
            }

        }

    }

    return true;
}
