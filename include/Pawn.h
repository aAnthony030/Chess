#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <utility>
#include "Struct.h"
#include "Struct.h"

using namespace std;

class Pawn {
    public:

        vector<pair<float,float>> pawn_movement(Piece& piece, vector<Piece> pieces) {
            
            vector<pair<float,float>> possibleMoves;
            const int cellsize = 80;
            bool is_piece_in_front = false; // I check that there is no piece in front of the pawn to allow it to move forward 2 places
            if(piece.isWhite) {
                // first pawn movement
                if(piece.position.y == 480) {
                    possibleMoves.push_back({piece.position.x, piece.position.y - cellsize});      // 1 square forward

                    for (int i = pieces.size() - 1; i >= 0; i--) {
                        if (pieces[i].position.x == piece.position.x && (pieces[i].position.y == (piece.position.y - cellsize))) {
                            is_piece_in_front = true;
                        }    
                    }
                    if (!is_piece_in_front) {
                        possibleMoves.push_back({piece.position.x, piece.position.y - 2*cellsize});    // 2 square forward
                    }

                    possibleMoves.push_back({piece.position.x - cellsize, piece.position.y - cellsize}); // left capture
                    possibleMoves.push_back({piece.position.x + cellsize, piece.position.y - cellsize}); // right capture
                } 
                
                else {
                    possibleMoves.push_back({piece.position.x, piece.position.y - cellsize});      // 1 square forward
                    possibleMoves.push_back({piece.position.x - cellsize, piece.position.y - cellsize}); // left capture
                    possibleMoves.push_back({piece.position.x + cellsize, piece.position.y - cellsize}); // right capture
                }

                
            } 
            
            else {
                // black pieces
                if(piece.position.y == 80) {
                    possibleMoves.push_back({piece.position.x, piece.position.y + cellsize});      // 1 square forward

                    for (int i = pieces.size() - 1; i >= 0; i--) {
                        if (pieces[i].position.x == piece.position.x && (pieces[i].position.y == (piece.position.y + cellsize))) {
                            is_piece_in_front = true;
                        }    
                    }
                    if (!is_piece_in_front) {
                        possibleMoves.push_back({piece.position.x, piece.position.y + 2*cellsize});    // 2 square forward
                    }
                    
                    possibleMoves.push_back({piece.position.x + cellsize, piece.position.y + cellsize}); // right capture
                    possibleMoves.push_back({piece.position.x - cellsize, piece.position.y + cellsize}); // left capture
                } 
                
                else {
                    possibleMoves.push_back({piece.position.x, piece.position.y + cellsize});      // 1 square forward
                    possibleMoves.push_back({piece.position.x - cellsize, piece.position.y + cellsize}); // right capture
                    possibleMoves.push_back({piece.position.x + cellsize, piece.position.y + cellsize}); // left capture
                }

            }

            return possibleMoves;
        }

};
