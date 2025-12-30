#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <utility>
#include "Struct.h"

using namespace std;

class Rook {
    public:

        vector<pair<float,float>> rook_movement(Piece& piece) {
            
            vector<pair<float,float>> possibleMoves;
            const int cellsize = 80;

            for(int i = cellsize; i < 640; i+=cellsize) {
                possibleMoves.push_back({piece.position.x + i, piece.position.y}); // 0 - 7 (destra)
            }

            for(int i = cellsize; i < 640; i+=cellsize) {
                possibleMoves.push_back({piece.position.x, piece.position.y + i}); // 8 - 15 (giù)
            }

            for(int i = cellsize; i < 640; i+=cellsize) {
                possibleMoves.push_back({piece.position.x - i, piece.position.y}); // 16 - 23 (sinistra)  
            }

            for(int i = cellsize; i < 640; i+=cellsize) {
                possibleMoves.push_back({piece.position.x, piece.position.y - i}); // 24 - 31 (su)     
            }

            return possibleMoves;

        }

};
