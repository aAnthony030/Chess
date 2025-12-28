#ifndef ENDGAME_H
#define ENDGAME_H

#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <cmath>
#include "SpecialMoves.h"
#include "Struct.h"
#include "Pawn.h"
#include "King.h"
#include "Knight.h"
#include "Queen.h"
#include "LegalMove.h"

class LegalMove;

bool Check(vector<Piece>& pieces, bool whiteTurn) {

    Pawn pawnC;
    King  kingC;
    Knight knightC;
    Rook rookC;
    Bishop bishopC;
    Queen queenC;
    // LegalMove legal_moveC;
    vector <pair<float,float>> moves;

    int king_index = -1;
    for (int i = 0; i < pieces.size(); i++) {
        if (pieces[i].type == KING && pieces[i].isWhite == whiteTurn) {
            king_index = i;
            break;
        }

    } 

    if (king_index == -1) return false;

    for (int i = 0; i < pieces.size(); i++) {

        if (pieces[i].isWhite != pieces[king_index].isWhite) {
            switch (pieces[i].type) {
                                    
                case PAWN:
    
                    moves = pawnC.pawn_movement(pieces[i]);
                    break;
                                    
                case KING:

                    moves = kingC.king_movement(pieces[i], pieces);
                    break;
                                    
                case KNIGHT:

                    moves = knightC.knight_movement(pieces[i]);
                    break;
                                
                case ROOK:
                    // TODO: CRTP
                    // legal_moveC.checkRookMoves(pieces, moves, pieces[i], true);
                    break;  
                                    
                case BISHOP:
                    // TODO: CRTP          
                    //legal_moveC.checkBishopMoves(pieces, moves, pieces[i], true); 
                    break;  
                                    
                case QUEEN:
                    // TODO: CRTP             
                    // legal_moveC.checkRookMoves(pieces, moves, pieces[i], true);
                    // legal_moveC.checkBishopMoves(pieces, moves, pieces[i], true); 
                    break; 

            }

            for (int j = 0; j < moves.size(); j++) {
                if (moves[j].first == pieces[king_index].position.x && moves[j].second == pieces[king_index].position.y) {
                    return true;
                }

            }

        }

    }

    return false;

}
// simulo la scacchiera per testare ogni possibile mossa e vedere se protegge il re
bool isMoveLegal(Piece singoloPiece, vector<Piece> pieces, pair<float,float> move) {
    for (int i = 0; i < pieces.size(); i++) {

        if (pieces[i].position.x == singoloPiece.position.x && 
        pieces[i].position.y == singoloPiece.position.y &&
        pieces[i].isWhite == singoloPiece.isWhite) {

            pieces[i].position.x = move.first;
            pieces[i].position.y = move.second;
            break;
        }

    }

    return Check(pieces, singoloPiece.isWhite);

}

void Checkmate() {
    // TODO
}

void Stall() {
    // TODO
}


#endif