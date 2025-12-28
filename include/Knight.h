#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <utility>
#include "Struct.h"
#include "Struct.h"

using namespace std;

class Knight {
    public:

        vector<pair<float,float>> knight_movement(Piece& piece) {
            
            vector<pair<float,float>> possibleMoves;
            const int cellsize = 80;

            possibleMoves.push_back({piece.position.x + cellsize, piece.position.y - (2 * cellsize)}); // Cavallo avanti destra (2 in alto 1 a destra)
            possibleMoves.push_back({piece.position.x - cellsize, piece.position.y - (2 * cellsize)}); // Cavallo avanti sinistra (2 in alto 1 a sinistra)
            possibleMoves.push_back({piece.position.x + cellsize, piece.position.y + (2 * cellsize)}); // Cavallo in basso destra (2 in basso 1 a destra)
            possibleMoves.push_back({piece.position.x - cellsize, piece.position.y + (2 * cellsize)}); // Cavallo in basso sinistra (2 in basso 1 a sinistra)
            possibleMoves.push_back({piece.position.x + (2 * cellsize), piece.position.y - cellsize}); // Cavallo avanti destra (1 in alto 2 a destra)
            possibleMoves.push_back({piece.position.x - (2 * cellsize), piece.position.y - cellsize}); // Cavallo avanti sinistra (1 in alto 2 a sinistra)
            possibleMoves.push_back({piece.position.x + (2 * cellsize), piece.position.y + cellsize}); // Cavallo in basso destra (1 in basso 2 a sinistra)
            possibleMoves.push_back({piece.position.x - (2 * cellsize), piece.position.y + cellsize}); // Cavallo in basso sinistra (1 in basso 2 a sinistra)
            
            return possibleMoves;

        }

};
