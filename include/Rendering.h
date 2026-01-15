#pragma once

#include "Struct.h"

template <typename T>

void Rendering(T* renderer, vector<Piece> pieces) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);  
            
        int cellsize = 80;
    
        for(int row = 0; row < 8; row++) {
    
            for(int col = 0; col < 8; col++) {
                    
                SDL_FRect cell { float(col * cellsize), float(row * cellsize), float(cellsize), float(cellsize)};
    
                if(!((row +  col) % 2)) {
                    SDL_SetRenderDrawColor(renderer, 240, 217, 181, 255); // casella chiaro
                }
    
                else {
                    SDL_SetRenderDrawColor(renderer, 181, 136, 99, 255);  // casella scuro
                }
    
                SDL_RenderFillRect(renderer, &cell);
            }
    
        }
        SidebarRendering(renderer);
            
        for(int i = 0; i < pieces.size(); i++) {
    
            if(pieces[i].texture && pieces[i].alive) {
                SDL_RenderTexture(renderer, pieces[i].texture, nullptr, &pieces[i].position);
            }
                
    
        }
        SDL_RenderPresent(renderer);

}

template <typename T>

void SidebarRendering(T* renderer) {
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_FRect sidebar = {640, 0, 180, 640};
        SDL_RenderFillRect(renderer, &sidebar);
}