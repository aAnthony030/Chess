#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <utility>
#include "Struct.h"
#include "Struct.h"

using namespace std;

class Pawn {
    public:

        vector<pair<float,float>> pawn_movement(Piece& piece) {
            
            vector<pair<float,float>> possibleMoves;
            const int cellsize = 80;

            if(piece.isWhite) {
                // Primo movimento pedone
                if(piece.position.y == 480) {
                    possibleMoves.push_back({piece.position.x, piece.position.y - cellsize});      // 1 casella avanti
                    possibleMoves.push_back({piece.position.x, piece.position.y - 2*cellsize});    // 2 caselle avanti
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
                    possibleMoves.push_back({piece.position.x, piece.position.y + 2*cellsize});    // 2 caselle avanti
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
