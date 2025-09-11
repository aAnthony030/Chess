#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <iostream>

using namespace std;

int main() {
    SDL_Window *window; 
    SDL_Renderer* renderer;
    SDL_Texture *whiteRookTexture, *whitePawnTexture, *whiteKingTexture, 
                *whiteQueenTexture, *whiteBishopTexture, *whiteKnightTexture,
                *blackRookTexture, *blackPawnTexture, *blackKingTexture, 
                *blackQueenTexture, *blackBishopTexture, *blackKnightTexture;   
    SDL_Event event;

    bool running = true;
    
    SDL_Init(SDL_INIT_VIDEO);
    if(!SDL_Init(SDL_INIT_VIDEO) ){
        cerr << "Errore inizializzazione SDL: " << SDL_GetError() << endl;
        return 1;
    }

    window = SDL_CreateWindow("Chess", 640, 640, SDL_WINDOW_RESIZABLE);
    if (!window) {
        cerr << "Errore creazione finestra: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        cerr << "Errore creazione renderer: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }
    //pezzi bianchi
    whiteRookTexture = IMG_LoadTexture(renderer, "C:\\Projects\\Game\\pieces\\white-rook.png");
    whitePawnTexture = IMG_LoadTexture(renderer, "C:\\Projects\\Game\\pieces\\white-pawn.png");
    whiteKingTexture = IMG_LoadTexture(renderer, "C:\\Projects\\Game\\pieces\\white-king.png");
    whiteQueenTexture = IMG_LoadTexture(renderer, "C:\\Projects\\Game\\pieces\\white-queen.png");
    whiteBishopTexture = IMG_LoadTexture(renderer, "C:\\Projects\\Game\\pieces\\white-bishop.png");
    whiteKnightTexture = IMG_LoadTexture(renderer, "C:\\Projects\\Game\\pieces\\white-knight.png");
    //pezzi neri
    blackRookTexture = IMG_LoadTexture(renderer, "C:\\Projects\\Game\\pieces\\black-rook.png");
    blackPawnTexture = IMG_LoadTexture(renderer, "C:\\Projects\\Game\\pieces\\black-pawn.png");
    blackKingTexture = IMG_LoadTexture(renderer, "C:\\Projects\\Game\\pieces\\black-king.png");
    blackQueenTexture = IMG_LoadTexture(renderer, "C:\\Projects\\Game\\pieces\\black-queen.png");
    blackBishopTexture = IMG_LoadTexture(renderer, "C:\\Projects\\Game\\pieces\\black-bishop.png");
    blackKnightTexture = IMG_LoadTexture(renderer, "C:\\Projects\\Game\\pieces\\black-knight.png");
 
    if(!whiteRookTexture || !whitePawnTexture || !whiteKingTexture || 
       !whiteQueenTexture || !whiteBishopTexture || !whiteKnightTexture){
        cerr << "Errore IMG_LoadTexture: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }



    while(running){

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
                    SDL_SetRenderDrawColor(renderer, 240, 217, 181, 255); // casella chiaro
                }
                else {
                    SDL_SetRenderDrawColor(renderer, 181, 136, 99, 255);  // casella scuro
                }
                SDL_RenderFillRect(renderer, &cell);
            }
        }
        
        //torre - cavallo - alfiere bianchi
        for(int i = 0; i < 2; i++){
            SDL_FRect whiteRookPos{ float(i*560), float(560), float(80), float(80) };
            SDL_RenderTexture(renderer, whiteRookTexture, nullptr, &whiteRookPos);
            SDL_FRect whiteKnightPos{ float(80 + 400*i), float(560), float(80), float(80) };
            SDL_RenderTexture(renderer, whiteKnightTexture, nullptr, &whiteKnightPos);
            SDL_FRect whiteBishopPos{ float(160 + 240*i), float(560), float(80), float(80) };
            SDL_RenderTexture(renderer, whiteBishopTexture, nullptr, &whiteBishopPos);
            //torre - cavallo - alfiere neri
            SDL_FRect blackRookPos{ float(i*560), float(0), float(80), float(80) };
            SDL_RenderTexture(renderer, blackRookTexture, nullptr, &blackRookPos);
            SDL_FRect blackKnightPos{ float(80 + 400*i), float(0), float(80), float(80) };
            SDL_RenderTexture(renderer, blackKnightTexture, nullptr, &blackKnightPos);
            SDL_FRect blackBishopPos{ float(160 + 240*i), float(0), float(80), float(80) };
            SDL_RenderTexture(renderer, blackBishopTexture, nullptr, &blackBishopPos);
        }
        for(int i = 0; i<8; i++) {
            //pedoni bianchi
            SDL_FRect  whitePawnPos{ float(80*i), float(480), float(80), float(80) };
            SDL_RenderTexture(renderer, whitePawnTexture, nullptr, &whitePawnPos);
            //pedoni neri
            SDL_FRect  blackPawnPos{ float(80*i), float(80), float(80), float(80) };
            SDL_RenderTexture(renderer, blackPawnTexture, nullptr, &blackPawnPos);
        }
        //re - regina bianchi
        SDL_FRect whiteQueenPos{ float(240), float(560), float(80), float(80) };
        SDL_RenderTexture(renderer, whiteQueenTexture, nullptr, &whiteQueenPos);
        SDL_FRect whiteKingPos{ float(320), float(560), float(80), float(80) };
        SDL_RenderTexture(renderer, whiteKingTexture, nullptr, &whiteKingPos);
        //re - regina neri
        SDL_FRect blackQueenPos{ float(320), float(0), float(80), float(80) };
        SDL_RenderTexture(renderer, blackQueenTexture, nullptr, &blackQueenPos);
        SDL_FRect blackKingPos{ float(240), float(0), float(80), float(80) };
        SDL_RenderTexture(renderer, blackKingTexture, nullptr, &blackKingPos);
        SDL_RenderPresent(renderer);
    // --- fine texture pezzi ---


    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    //SDL_DestroyTexture(rookTexture); //TODO: modificare e distruggere tutte le texture
    SDL_Quit();
}
