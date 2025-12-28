#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <utility>
#include "Bishop.h"
#include "Rook.h"
#include "Struct.h"

using namespace std;

class Queen {
    public:
        Rook rookC;
        Bishop bishopC;
        vector<pair<float,float>> queen_movement(Piece& piece) {
            
            vector<pair<float, float>> rook = rookC.rook_movement(piece);
            vector<pair<float, float>> possibleMoves;

            possibleMoves.insert(possibleMoves.end(), rook.begin(), rook.end());
            
            return possibleMoves;
        }

};