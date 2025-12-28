#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <utility>
#include "Struct.h"

using namespace std;

class King {
    public:

        vector<pair<float,float>> king_movement(Piece& piece, vector<Piece>& pieces) {
            
            vector<pair<float,float>> possibleMoves;
            const int cellsize = 80;


            possibleMoves.push_back({piece.position.x, piece.position.y - cellsize}); // Re avanti
            possibleMoves.push_back({piece.position.x, piece.position.y + cellsize}); // Re indietro
            possibleMoves.push_back({piece.position.x - cellsize, piece.position.y}); // Re sinistra
            possibleMoves.push_back({piece.position.x + cellsize, piece.position.y}); // Re destra
            possibleMoves.push_back({piece.position.x - cellsize, piece.position.y - cellsize}); // Re in alto sinistra
            possibleMoves.push_back({piece.position.x + cellsize, piece.position.y - cellsize}); // Re in alto destra
            possibleMoves.push_back({piece.position.x - cellsize, piece.position.y + cellsize}); // Re in basso sinistra
            possibleMoves.push_back({piece.position.x + cellsize, piece.position.y + cellsize}); // Re in basso destra
            if (castling(piece, pieces, true)) {
                possibleMoves.push_back({piece.position.x + (2 * cellsize), piece.position.y}); // arrocco corto
            }
            if (castling(piece, pieces, false)) {
                possibleMoves.push_back({piece.position.x - (2 * cellsize), piece.position.y}); // arrocco lungo
            }

            return possibleMoves;
        }

};