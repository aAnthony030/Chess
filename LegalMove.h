#pragma once

#include <SDL3/SDL.h>
#include <vector>

template <typename T, typename U, typename V>
class LegalMove {
    public:

        void CheckMoves(T pieces, U& moves, V singoloPiece) {
            
            for(int i = 0; i < moves.size(); i++) {
                //controllo se la mossa viene proposta all'interno dei limiti della scacchiera
                if(moves[i].first < 0 || moves[i].first > 640 || moves[i].second < 0 || moves[i].second > 640) {
                    moves.erase(moves.begin() + i);
                    break;
                }

                for(int j = 0; j < pieces.size(); j++) {
                    if((moves[i].first == pieces[j].position.x && moves[i].second == pieces[j].position.y && 
                    pieces[i].isWhite == pieces[j].isWhite) || singoloPiece.position.y - 80 == pieces[j].position.y) {
                        moves.erase(moves.begin() + i);
                        break;
                    }

                }

            }

        }

};

