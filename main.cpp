#include <SDL3/SDL.h>
#include <iostream>

using namespace std;

int main() {
    SDL_Window *window; 
    SDL_Renderer* renderer;
    bool running = true;
    
    SDL_Init(SDL_INIT_VIDEO);
    
    window = SDL_CreateWindow("danilo puzza", 640, 640, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, nullptr);

    while(running){

        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        
        int cellsize = 80;

        for(int row = 0; row < 8; row++) {
            for(int col = 0; col < 8; col++) {
                SDL_FRect cell { float(col * cellsize), float(row * cellsize), float(cellsize), float(cellsize)};

                if(!((row +  col) % 2)) {
                    SDL_SetRenderDrawColor(renderer, 240, 217, 181, 255); // chiaro
                }
                else {
                    SDL_SetRenderDrawColor(renderer, 181, 136, 99, 255);  // scuro
                }
                SDL_RenderFillRect(renderer, &cell);
            }
        }
        SDL_RenderPresent(renderer);
        SDL_DestroyRenderer(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
