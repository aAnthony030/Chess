#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <utility>
#include "Struct.h"

using namespace std;

class King {
    public:

        vector<pair<float,float>> king_movement(Piece& piece, vector<Piece>& pieces, bool& short_castle, bool& long_castle) {
            
            vector<pair<float,float>> possibleMoves;
            const int cellsize = 80;


            possibleMoves.push_back({piece.position.x, piece.position.y - cellsize}); // king forward
            possibleMoves.push_back({piece.position.x, piece.position.y + cellsize}); // king backward
            possibleMoves.push_back({piece.position.x - cellsize, piece.position.y}); // king left
            possibleMoves.push_back({piece.position.x + cellsize, piece.position.y}); // king right
            possibleMoves.push_back({piece.position.x - cellsize, piece.position.y - cellsize}); // king up left
            possibleMoves.push_back({piece.position.x + cellsize, piece.position.y - cellsize}); // king up right
            possibleMoves.push_back({piece.position.x - cellsize, piece.position.y + cellsize}); // king bottom left
            possibleMoves.push_back({piece.position.x + cellsize, piece.position.y + cellsize}); // king bottom right
            if (castling(piece, pieces, true)) {
                possibleMoves.push_back({piece.position.x + (2 * cellsize), piece.position.y}); // short castling
                short_castle = true;
            }
            if (castling(piece, pieces, false)) {
                possibleMoves.push_back({piece.position.x - (2 * cellsize), piece.position.y}); // long castling
                long_castle = true;
            }

            return possibleMoves;
        }

};