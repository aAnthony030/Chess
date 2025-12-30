#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <utility>
#include "Struct.h"

using namespace std;

        // avendo cambiato metodo per controllare le mosse legali dell'alfiere ora le mosse valide
        // non vengono generate prima e tolte dopo ma viene fatto il controllo man mano e vengono
        //aggiunte solo le mosse valide
class Bishop {
    public:

        vector<pair<float,float>> bishop_movement(Piece& piece) {
            
            vector<pair<float,float>> possibleMoves;
            const int cellsize = 80;

            for(int i = cellsize; i < 640; i+=cellsize) {
                possibleMoves.push_back({piece.position.x + i, piece.position.y + i}); // 0 - 7
            }

            for(int i = cellsize; i < 640; i+=cellsize) {
                possibleMoves.push_back({piece.position.x - i, piece.position.y + i}); // 8 - 15
            }

            for(int i = cellsize; i < 640; i+=cellsize) {
                possibleMoves.push_back({piece.position.x - i, piece.position.y - i}); // 16 - 23       
            }

            for(int i = cellsize; i < 640; i+=cellsize) {
                possibleMoves.push_back({piece.position.x + i, piece.position.y - i}); // 24 - 31      
            }

            
            return possibleMoves;

        }

};
