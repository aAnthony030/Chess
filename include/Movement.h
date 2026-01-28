#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <utility>
#include "Struct.h"

template <typename T>
class Movement {

    public:

        void movement(T event, vector<pair<float,float>> moves, Piece& piece, vector<Piece>& pieces, bool& whiteTurn, bool& piece_moved) {
            const int cellsize = 80;
            int tempX = piece.position.x;
            int tempY = piece.position.y;

            for(int i = 0; i < moves.size(); i++){

                if(event.button.x >= moves[i].first && event.button.x <= moves[i].first + cellsize &&
                event.button.y >= moves[i].second && event.button.y <= moves[i].second + cellsize){
                    
                    piece.position.x = moves[i].first;
                    piece.position.y = moves[i].second;
                    break;
                    
                }
                
            }
            // check that piece has been moved and not deselected
            if(tempX != piece.position.x  || tempY != piece.position.y) {

                whiteTurn = !whiteTurn;
                piece_moved = true;
                
            }
            //en passant check
            if (piece.type == PAWN) {

                for (int i = pieces.size() - 1; i >= 0; i--) {

                    if (pieces[i].type != PAWN || pieces[i].isWhite == piece.isWhite) continue;

                    if (pieces[i].vulnerable_enPassant &&
                    pieces[i].position.x == piece.position.x &&
                    pieces[i].position.y == (piece.isWhite ? piece.position.y + 80: piece.position.y - 80)) {

                        pieces.erase(pieces.begin() + i);
                        break;
                    }

                }

            }

            // castling
            if (piece.type == KING && piece.first_move) {
                if (piece.position.x == 480 && (piece.position.y == 0 || piece.position.y == 560)) {
                    for (int i = pieces.size() - 1; i >= 0; i--) {
                    
                        if (pieces[i].type == ROOK && pieces[i].isWhite == piece.isWhite && pieces[i].position.x == 560
                        && pieces[i].first_move && pieces[i].position.y == piece.position.y) {
                            pieces[i].position.x = 400;
                            break;
                        }
                    
                    }

                }

                if(piece.position.x == 160 && (piece.position.y == 0 || piece.position.y == 560)) {
                    for (int i = pieces.size() - 1; i >= 0; i--) {
                    
                        if (pieces[i].type == ROOK && pieces[i].isWhite == piece.isWhite && pieces[i].position.x == 0
                        && pieces[i].first_move && pieces[i].position.y == piece.position.y) {
                            pieces[i].position.x = 240;
                            break;
                        }
                    
                    }
                    
                }

            }

        }

};