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

            possibleMoves.push_back({piece.position.x + cellsize, piece.position.y - (2 * cellsize)}); // Horse forward right (2 up 1 right)
            possibleMoves.push_back({piece.position.x - cellsize, piece.position.y - (2 * cellsize)}); // Horse bottom right (2 bottom 1 right)
            possibleMoves.push_back({piece.position.x + cellsize, piece.position.y + (2 * cellsize)}); // Cavallo in basso destra (2 in basso 1 a destra)
            possibleMoves.push_back({piece.position.x - cellsize, piece.position.y + (2 * cellsize)}); // Horse bottom left (2 bottom 1 left)
            possibleMoves.push_back({piece.position.x + (2 * cellsize), piece.position.y - cellsize}); // Horse forward right (1 up 2 right)
            possibleMoves.push_back({piece.position.x - (2 * cellsize), piece.position.y - cellsize}); // Horse forward left (1 up 2 left)
            possibleMoves.push_back({piece.position.x + (2 * cellsize), piece.position.y + cellsize}); // Horse bottom right (1 bottom 2 left)
            possibleMoves.push_back({piece.position.x - (2 * cellsize), piece.position.y + cellsize}); // Horse bottom left (1 bottom 2 left)
            
            return possibleMoves;

        }

};
