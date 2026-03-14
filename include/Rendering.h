#pragma once

#include "Struct.h"

template <typename T>

void Rendering(T* renderer, vector<Piece> pieces) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);  
            
        int cellsize = 80;
        SDL_Texture* button_texture = IMG_LoadTexture(renderer, "font/play_again_button.png");
    
        for(int row = 0; row < 8; row++) {
    
            for(int col = 0; col < 8; col++) {
                    
                SDL_FRect cell { float(col * cellsize), float(row * cellsize), float(cellsize), float(cellsize)};
    
                if(!((row +  col) % 2)) {
                    SDL_SetRenderDrawColor(renderer, 240, 217, 181, 255); // white square
                }
    
                else {
                    SDL_SetRenderDrawColor(renderer, 181, 136, 99, 255);  // black square
                }
    
                SDL_RenderFillRect(renderer, &cell);
            }
    
        }
        SidebarRendering(renderer);

        SDL_FRect button_position = {590, 550, 300, 95};
        SDL_RenderTexture(renderer, button_texture, nullptr, &button_position);

        for(int i = 0; i < pieces.size(); i++) {
    
            if(pieces[i].texture && pieces[i].alive) {
                SDL_RenderTexture(renderer, pieces[i].texture, nullptr, &pieces[i].position);
            }
                
        }

}

template <typename T>

void SidebarRendering(T* renderer) {
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_FRect sidebar = {640, 0, 200, 640};
        SDL_RenderFillRect(renderer, &sidebar);
} 