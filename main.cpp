#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <iostream>
#include <vector>

using namespace std;

enum PieceTypes {
    pawn, bishop, knight, rook, queen, king
};

struct Piece {
    SDL_Texture* texture;
    int row, col;
    bool isWhite;
    enum PieceTypes type;
    SDL_FRect position;
};

vector<Piece> PiecesTexture(SDL_Renderer* renderer) {
    SDL_Texture *whiteRookTexture, *whitePawnTexture, *whiteKingTexture, 
                *whiteQueenTexture, *whiteBishopTexture, *whiteKnightTexture,
                *blackRookTexture, *blackPawnTexture, *blackKingTexture, 
                *blackQueenTexture, *blackBishopTexture, *blackKnightTexture;   
    vector<Piece> pieces;
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


    for(int i = 0; i < 8; i++) {
        // pieces[0] -> pieces[7]: pedoni bianchi
        pieces.push_back({whitePawnTexture, i, 1, true, pawn, { float(80*i), float(480), float(80), float(80) } });
    }
    for(int i = 0; i < 2; i++) {
        // pieces[8] -> pieces[9]: torri bianche
        pieces.push_back({whiteRookTexture, i * 7, 0, true, rook, { float(i*560), float(560), float(80), float(80) } });
    }
    for(int i = 0; i <= 1; i++) {
        // pieces[10] -> pieces[11]: cavalli bianchi
        pieces.push_back({whiteKnightTexture, i , 0, true, knight, { float(80 + 400*i), float(560), float(80), float(80) } });
    }
    for(int i = 0; i <= 1; i++) {
        // pieces[12] -> pieces[13]: alfieri bianchi
        pieces.push_back({whiteBishopTexture, i , 0, true, bishop, { float(160 + 240*i), float(560), float(80), float(80) } });
    }
    pieces.push_back({whiteQueenTexture, 4 , 0, true, queen, { float(240), float(560), float(80), float(80) } }); //pieces[14]: regina bianca
    pieces.push_back({whiteKingTexture, 3 , 0, true, king, { float(320), float(560), float(80), float(80) } }); // pieces[15]: re bianco

    for(int i = 0; i < 8; i++) {
        // pieces[16] -> pieces[23]: pedoni neri
        pieces.push_back({blackPawnTexture, i, 6, false, pawn, { float(80*i), float(80), float(80), float(80) } });
    }
    for(int i = 0; i < 2; i++) {
        // pieces[24] -> pieces[25]: torri nere
        pieces.push_back({blackRookTexture, i * 7, 7, false, rook, { float(i*560), float(0), float(80), float(80) } });
    }
    for(int i = 0; i <= 1 ; i++) {
        // pieces[26] -> pieces[27]: cavalli neri
        pieces.push_back({blackKnightTexture, i , 7, false, knight, { float(80 + 400*i), float(0), float(80), float(80) } });
    }
    for(int i = 0; i <= 1; i++) {
        // pieces[28] -> pieces[29]: alfieri neri
        pieces.push_back({blackBishopTexture, i , 7, false, bishop, { float(160 + 240*i), float(0), float(80), float(80) } });
    }
    pieces.push_back({blackQueenTexture, 3 , 7, false, queen, { float(320), float(0), float(80), float(80) } }); //pieces[30]: regina nera
    pieces.push_back({blackKingTexture, 4 , 7, false, king, { float(240), float(0), float(80), float(80) } }); // pieces[31]: re nero

    return pieces;
}


int main() {
    SDL_Renderer* renderer;
    SDL_Window *window; 
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

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        cerr << "Errore creazione renderer: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }
 
    vector<Piece> pieces = PiecesTexture(renderer);

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

        for(int i = 0; i < pieces.size(); i++) {
            if(pieces[i].texture) {
                SDL_RenderTexture(renderer, pieces[i].texture, nullptr, &pieces[i].position);
            }
        }
        SDL_RenderPresent(renderer);                                                   
    }                                                                       

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    for(auto texture: pieces) {
        SDL_DestroyTexture(texture.texture); //TODO: modificare e distruggere tutte le texture
    }
    SDL_Quit();
}