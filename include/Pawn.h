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
            bool is_piece_in_front = false; // controllo che davanti al pedone non ci sia nessun pezzo per permettergli di avanzare di 2 posti
            if(piece.isWhite) {
                // Primo movimento pedone
                if(piece.position.y == 480) {
                    possibleMoves.push_back({piece.position.x, piece.position.y - cellsize});      // 1 casella avanti

                    for (int i = pieces.size() - 1; i >= 0; i--) {
                        if (pieces[i].position.x == piece.position.x && (pieces[i].position.y == (piece.position.y - cellsize))) {
                            is_piece_in_front = true;
                        }    
                    }
                    if (!is_piece_in_front) {
                        possibleMoves.push_back({piece.position.x, piece.position.y - 2*cellsize});    // 2 caselle avanti
                    }

                    possibleMoves.push_back({piece.position.x - cellsize, piece.position.y - cellsize}); // cattura sinistra
                    possibleMoves.push_back({piece.position.x + cellsize, piece.position.y - cellsize}); // cattura destra
                } 
                
                else {
                    possibleMoves.push_back({piece.position.x, piece.position.y - cellsize});      // 1 casella avanti
                    possibleMoves.push_back({piece.position.x - cellsize, piece.position.y - cellsize}); // cattura sinistra
                    possibleMoves.push_back({piece.position.x + cellsize, piece.position.y - cellsize}); // cattura destra
                }

                
            } 
            
            else {
                // Pedoni neri
                if(piece.position.y == 80) {
                    possibleMoves.push_back({piece.position.x, piece.position.y + cellsize});      // 1 casella avanti

                    for (int i = pieces.size() - 1; i >= 0; i--) {
                        if (pieces[i].position.x == piece.position.x && (pieces[i].position.y == (piece.position.y + cellsize))) {
                            is_piece_in_front = true;
                        }    
                    }
                    if (!is_piece_in_front) {
                        possibleMoves.push_back({piece.position.x, piece.position.y + 2*cellsize});    // 2 caselle avanti
                    }
                    
                    possibleMoves.push_back({piece.position.x + cellsize, piece.position.y + cellsize}); // cattura destra
                    possibleMoves.push_back({piece.position.x - cellsize, piece.position.y + cellsize}); // cattura sinistra
                } 
                
                else {
                    possibleMoves.push_back({piece.position.x, piece.position.y + cellsize});      // 1 casella avanti
                    possibleMoves.push_back({piece.position.x - cellsize, piece.position.y + cellsize}); // cattura destra
                    possibleMoves.push_back({piece.position.x + cellsize, piece.position.y + cellsize}); // cattura sinistra
                }

            }

            return possibleMoves;
        }

};
