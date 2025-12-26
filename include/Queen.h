#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <utility>
#include "Bishop.h"
#include "Rook.h"
using namespace std;

template <typename T>
class Queen {
    public:
        Rook <T> rookC;
        Bishop <T> bishopC;
        vector<pair<float,float>> queen_movement(T& piece) {
            
            vector<pair<float, float>> rook = rookC.rook_movement(piece);
            vector<pair<float, float>> possibleMoves;

            possibleMoves.insert(possibleMoves.end(), rook.begin(), rook.end());
            
            return possibleMoves;
        }

};