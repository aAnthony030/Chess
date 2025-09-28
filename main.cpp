#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <iostream>
#include <vector>
#include <utility>
#include "include/Pawn.h"
#include "include/Rendering.h"
#include "include/LegalMove.h"
#include "include/Movement.h"
#include "include/King.h"
#include "include/Knight.h"

using namespace std;

enum PieceTypes {
    PAWN, BISHOP, KNIGHT, ROOK, QUEEN, KING
};

struct Piece {
    SDL_Texture* texture;
    bool isWhite;
    enum PieceTypes type;
    SDL_FRect position;
    bool alive = true;
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
        pieces.push_back({whitePawnTexture, true, PAWN, { float(80*i), float(480), float(80), float(80) } });
    }

    for(int i = 0; i < 2; i++) {
        // pieces[8] -> pieces[9]: torri bianche
        pieces.push_back({whiteRookTexture, true, ROOK, { float(i*560), float(560), float(80), float(80) } });
    }

    for(int i = 0; i <= 1; i++) {
        // pieces[10] -> pieces[11]: cavalli bianchi
        pieces.push_back({whiteKnightTexture, true, KNIGHT, { float(80 + 400*i), float(560), float(80), float(80) } });
    }

    for(int i = 0; i <= 1; i++) {
        // pieces[12] -> pieces[13]: alfieri bianchi
        pieces.push_back({whiteBishopTexture, true, BISHOP, { float(160 + 240*i), float(560), float(80), float(80) } });
    }
    pieces.push_back({whiteQueenTexture, true, QUEEN, { float(320), float(560), float(80), float(80) } }); //pieces[14]: regina bianca
    pieces.push_back({whiteKingTexture, true, KING, { float(240), float(560), float(80), float(80) } }); // pieces[15]: re bianco

    for(int i = 0; i < 8; i++) {
        // pieces[16] -> pieces[23]: pedoni neri
        pieces.push_back({blackPawnTexture, false, PAWN, { float(80*i), float(80), float(80), float(80) } });
    }

    for(int i = 0; i < 2; i++) {
        // pieces[24] -> pieces[25]: torri nere
        pieces.push_back({blackRookTexture, false, ROOK, { float(i*560), float(0), float(80), float(80) } });
    }

    for(int i = 0; i <= 1 ; i++) {
        // pieces[26] -> pieces[27]: cavalli neri
        pieces.push_back({blackKnightTexture, false, KNIGHT, { float(80 + 400*i), float(0), float(80), float(80) } });
    }

    for(int i = 0; i <= 1; i++) {
        // pieces[28] -> pieces[29]: alfieri neri
        pieces.push_back({blackBishopTexture, false, BISHOP, { float(160 + 240*i), float(0), float(80), float(80) } });
    }
    pieces.push_back({blackQueenTexture, false, QUEEN, { float(240), float(0), float(80), float(80) } }); //pieces[30]: regina nera
    pieces.push_back({blackKingTexture, false, KING, { float(320), float(0), float(80), float(80) } }); // pieces[31]: re nero

    return pieces;
}



int main() {
    Movement <SDL_Event, vector<pair<float,float>>, Piece&, vector<Piece>&, bool&> movementC;
    LegalMove <vector<Piece>, vector<pair<float,float>>&, Piece> legal_moveC;
    Pawn <Piece> pawnC;
    King <Piece> kingC;
    Knight <Piece> knightC;
    SDL_Renderer* renderer;
    SDL_Window *window; 
    SDL_Event event;

    vector<pair<float,float>> moves;
    bool running = true;
    bool selectedPieceBool = false;
    bool whiteTurn = true;

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
    int selectedPieceIndex;

    while(running){

        while (SDL_PollEvent(&event)) {
        
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }

            else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN ) {
                
                int x = event.button.x;
                int y = event.button.y;
                
                for(int i = 0; i < pieces.size(); i++) {

                    // controllo per vedere che il click del mouse corrisponda  
                    // alla casella occupata da un pezzo della scacchiera
                    if( (x >= pieces[i].position.x && x <= pieces[i].position.x + pieces[i].position.w &&
                    y >= pieces[i].position.y && y <= pieces[i].position.y + pieces[i].position.h) || selectedPieceBool ) {

                        
                        if(!selectedPieceBool) {
                            selectedPieceIndex = i;

                            //controllo per gestione dei turni
                            if(pieces[selectedPieceIndex].isWhite == whiteTurn) {

                                switch (pieces[selectedPieceIndex].type) {
                                    
                                    case PAWN:
    
                                        moves = pawnC.pawn_movement(pieces[selectedPieceIndex]);
    
                                        selectedPieceBool = true;
                                        break;
                                    
                                    case KING:

                                        moves = kingC.king_movement(pieces[selectedPieceIndex]);

                                        selectedPieceBool = true;
                                        break;
                                    
                                    case KNIGHT:

                                        moves = knightC.knight_movement(pieces[selectedPieceIndex]);

                                        selectedPieceBool = true;
                                        break;

                            }
                            
                        }
                    
                        break;
                        }


                        else {

                            
                            switch (pieces[selectedPieceIndex].type) {

                                case PAWN:
                                    legal_moveC.checkPawnMoves(pieces, moves, pieces[selectedPieceIndex]);
                                    movementC.movement(event, moves, pieces[selectedPieceIndex], pieces, whiteTurn);

                                    selectedPieceBool = false;
                                    break;
                                
                                case KING:
                                    legal_moveC.checkKingMoves(pieces, moves, pieces[selectedPieceIndex]);
                                    movementC.movement(event, moves, pieces[selectedPieceIndex], pieces, whiteTurn);

                                    selectedPieceBool = false;
                                    break;

                                case KNIGHT:
                                    legal_moveC.checkKnightMoves(pieces, moves, pieces[selectedPieceIndex]);
                                    movementC.movement(event, moves, pieces[selectedPieceIndex], pieces, whiteTurn);

                                    selectedPieceBool = false;
                                    break;
                                
                            }
    
                        }
                    
                        break;

                    }
                    
                }

            }

        }

        // render part
        Rendering(renderer, pieces);                                              
    }                                                                       

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    for(auto texture : pieces) {
        SDL_DestroyTexture(texture.texture); //TODO: modificare e distruggere tutte le texture
    }
    SDL_Quit();
}