#pragma once

template <typename T, typename U>

void Rendering(T* renderer, U pieces, bool promotion_call) {
        if (promotion_call) {
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
    
            for(int i = 0; i < pieces.size(); i++) {
    
                if(pieces[i].texture && pieces[i].alive) {
                    SDL_RenderTexture(renderer, pieces[i].texture, nullptr, &pieces[i].position);
                }
                
    
            }
            SDL_RenderPresent(renderer);
        }


        else {

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
    
            for(int i = 0; i < pieces.size(); i++) {
    
                if(pieces[i].texture && pieces[i].alive) {
                    SDL_RenderTexture(renderer, pieces[i].texture, nullptr, &pieces[i].position);
                }
                
    
            }
            SDL_RenderPresent(renderer);
        }

}
