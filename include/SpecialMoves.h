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



void arrocco() {
}