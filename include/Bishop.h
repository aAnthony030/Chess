#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <utility>
using namespace std;

template <typename T>
        // avendo cambiato metodo per controllare le mosse legali dell'alfiere ora le mosse valide
        // non vengono generate prima e tolte dopo ma viene fatto il controllo man mano e vengono
        //aggiunte solo le mosse valide
class Bishop {
    public:

        vector<pair<float,float>> bishop_movement(T& piece) {
            
            vector<pair<float,float>> possibleMoves;

            return possibleMoves;

        }

};
