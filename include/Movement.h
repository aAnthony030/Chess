#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <utility>
#include "Struct.h"

template <typename T>
class Movement {

    public:

        void movement(T event, vector<pair<float,float>> moves, Piece& piece, vector<Piece>& pieces, bool& whiteTurn) {
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
            // controllo che il pezzo sia stato spostato e non deselezionato
            if(tempX != piece.position.x  || tempY != piece.position.y) {

                whiteTurn = !whiteTurn;

            }
            //en passant check
            if (piece.type == PAWN) {

                for (int i = 0; i < pieces.size(); i++) {

                    if (pieces[i].type != PAWN || pieces[i].isWhite == piece.isWhite) continue;

                    if (pieces[i].vulnerable_enPassant &&
                    pieces[i].position.x == piece.position.x &&
                    pieces[i].position.y == (piece.isWhite ? piece.position.y + 80: piece.position.y - 80)) {

                        pieces.erase(pieces.begin() + i);
                        break;
                    }

                }

            }

            //arrocco
            if (piece.type == KING) {
                if (piece.position.x == 480) {
                    for (int i = 0; i < pieces.size(); i++) {
                    
                        if (pieces[i].type == ROOK && (pieces[i].isWhite == piece.isWhite && pieces[i].position.x == 560)) {
                            pieces[i].position.x = 400;
                            break;
                        }
                    
                    }

                }

                if(piece.position.x == 160) {
                    for (int i = 0; i < pieces.size(); i++) {
                    
                        if (pieces[i].type == ROOK && (pieces[i].isWhite == piece.isWhite && pieces[i].position.x == 0)) {
                            pieces[i].position.x = 240;
                            break;
                        }
                    
                    }
                    
                }

            }

        }

};