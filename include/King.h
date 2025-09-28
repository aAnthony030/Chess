#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <utility>
using namespace std;

template <typename T>
class King {
    public:

        vector<pair<float,float>> king_movement(T& piece) {
            
            vector<pair<float,float>> possibleMoves;
            const int cellsize = 80;

            if(piece.isWhite) {
                possibleMoves.push_back({piece.position.x, piece.position.y - cellsize}); // Re avanti
                possibleMoves.push_back({piece.position.x, piece.position.y + cellsize}); // Re indietro
                possibleMoves.push_back({piece.position.x - cellsize, piece.position.y}); // Re sinistra
                possibleMoves.push_back({piece.position.x + cellsize, piece.position.y}); // Re destra
                possibleMoves.push_back({piece.position.x - cellsize, piece.position.y - cellsize}); // Re in alto sinistra
                possibleMoves.push_back({piece.position.x + cellsize, piece.position.y - cellsize}); // Re in alto destra
                possibleMoves.push_back({piece.position.x - cellsize, piece.position.y + cellsize}); // Re in basso sinistra
                possibleMoves.push_back({piece.position.x + cellsize, piece.position.y + cellsize}); // Re in basso destra
            }

            else {
                possibleMoves.push_back({piece.position.x, piece.position.y + cellsize}); // Re avanti
                possibleMoves.push_back({piece.position.x, piece.position.y - cellsize}); // Re indietro
                possibleMoves.push_back({piece.position.x - cellsize, piece.position.y}); // Re sinistra
                possibleMoves.push_back({piece.position.x + cellsize, piece.position.y}); // Re destra
                possibleMoves.push_back({piece.position.x - cellsize, piece.position.y - cellsize}); // Re in basso sinistra
                possibleMoves.push_back({piece.position.x + cellsize, piece.position.y - cellsize}); // Re in basso destra
                possibleMoves.push_back({piece.position.x - cellsize, piece.position.y + cellsize}); // Re in alto sinistra
                possibleMoves.push_back({piece.position.x + cellsize, piece.position.y + cellsize}); // Re in alto destra
            }

            return possibleMoves;

        }

};
