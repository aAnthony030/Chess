#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <utility>

template <typename T, typename U, typename V, typename X>
class Movement {

    public:

        void movement(T event, U moves, V& piece, X& whiteTurn) {
            int cellsize = 80;
            int tempX = piece.position.x;
            int tempY = piece.position.y;

            for(int i = 0; i < moves.size(); i++){

                if(event.button.x >= moves[i].first && event.button.x <= moves[i].first + cellsize &&
                event.button.y >= moves[i].second && event.button.y <= moves[i].second + cellsize){
                    
                    piece.position.x = moves[i].first;
                    piece.position.y = moves[i].second;
                    
                    if(tempX != piece.position.x  || tempY != piece.position.x) {
                        whiteTurn = !whiteTurn;
                    }

                    break;

                }
                   
            }

        }

};