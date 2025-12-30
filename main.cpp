#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <iostream>
#include <vector>
#include <utility>
#include "include/Piecetypes.h"
#include "include/Pawn.h"
#include "include/Rendering.h"
#include "include/LegalMove.h"
#include "include/Movement.h"
#include "include/King.h"
#include "include/Knight.h"
#include "include/Rook.h"
#include "include/Bishop.h"
#include "include/Queen.h"
#include "include/Promotion.h"
#include "include/SpecialMoves.h"
#include "include/Struct.h"

using namespace std;
using PieceTypes::PAWN;
using PieceTypes::BISHOP;
using PieceTypes::KNIGHT;
using PieceTypes::ROOK;
using PieceTypes::QUEEN;
using PieceTypes::KING;


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
    pieces.push_back({whiteQueenTexture, true, QUEEN, { float(240), float(560), float(80), float(80) } }); //pieces[14]: regina bianca
    pieces.push_back({whiteKingTexture, true, KING, { float(320), float(560), float(80), float(80) } }); // pieces[15]: re bianco

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

void check_capture(vector<Piece>& pieces, Piece piece) {
    int index = -1;
    for (int i = 0; i < pieces.size(); i++) {
        if (pieces[i].position.x == piece.position.x && pieces[i].position.y == piece.position.y
        && pieces[i].isWhite == piece.isWhite) {
            index = i;
            break;
        }

    }

    for (int i = 0; i < pieces.size(); i++) {
        if (i == index) {
            continue;
        }
        if (piece.position.x == pieces[i].position.x && piece.position.y == pieces[i].position.y) {
            pieces.erase(pieces.begin() + i);
            break;
        }

    }

}

int main() {
    Movement <SDL_Event> movementC;
    LegalMove legal_moveC;
    Pawn pawnC;
    King kingC;
    Knight knightC;
    Rook rookC;
    Bishop bishopC;
    Queen queenC;
    SDL_Renderer* renderer;
    SDL_Window *window; 
    SDL_Event event;

    vector<pair<float,float>> moves;
    pair<vector<pair<float, float>>, vector<pair<float,float>>> queen_moves;
    bool running = true;
    bool selectedPieceBool = false;
    bool whiteTurn = true;
    int moves_counter = 0;

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

                                        moves = kingC.king_movement(pieces[selectedPieceIndex], pieces);

                                        selectedPieceBool = true;
                                        break;
                                    
                                    case KNIGHT:

                                        moves = knightC.knight_movement(pieces[selectedPieceIndex]);

                                        selectedPieceBool = true;
                                        break;
                                
                                    case ROOK:

                                        moves = rookC.rook_movement(pieces[selectedPieceIndex]);

                                        selectedPieceBool = true;
                                        break;  
                                    
                                    case BISHOP:

                                        moves = bishopC.bishop_movement(pieces[selectedPieceIndex]);

                                        selectedPieceBool = true;
                                        break;  
                                    
                                    case QUEEN:
                                    
                                        queen_moves = queenC.queen_movement(pieces[selectedPieceIndex]);

                                        selectedPieceBool = true;
                                        break; 

                                }
                            
                            }
                    
                        break;
                        }


                        else {

                            switch (pieces[selectedPieceIndex].type) {

                                case PAWN: {
                                    legal_moveC.checkPawnMoves(pieces, moves, pieces[selectedPieceIndex]);
                                    int old_y = pieces[selectedPieceIndex].position.y;
                                    movementC.movement(event, moves, pieces[selectedPieceIndex], pieces, whiteTurn);
                                    int delta_y = abs(old_y - pieces[selectedPieceIndex].position.y);
                                    
                                    for(int p = 0; p < pieces.size(); p++) {
                                        pieces[p].vulnerable_enPassant = false;
                                    }
                                    if (delta_y == 160) {
                                        pieces[selectedPieceIndex].vulnerable_enPassant = true;
                                    }
                                    
                                    selectedPieceBool = false;  

                                    if ((pieces[selectedPieceIndex].isWhite && pieces[selectedPieceIndex].position.y <= 0) || (!pieces[selectedPieceIndex].isWhite && pieces[selectedPieceIndex].position.y >= 560)) {
                                        rendering_promote(pieces[selectedPieceIndex], renderer, window);
                                    }
                                    if (pieces[selectedPieceIndex].first_move)  pieces[selectedPieceIndex].first_move = false;
                                    moves_counter += 1;
                                    break;
                                }

                                case KING:
                                    legal_moveC.checkKingMoves(pieces, moves, pieces[selectedPieceIndex]);
                                    movementC.movement(event, moves, pieces[selectedPieceIndex], pieces, whiteTurn);

                                    selectedPieceBool = false;
                                    if (pieces[selectedPieceIndex].first_move)  pieces[selectedPieceIndex].first_move = false;
                                    moves_counter += 1;
                                    break;

                                case KNIGHT:
                                    legal_moveC.checkKnightMoves(pieces, moves, pieces[selectedPieceIndex]);
                                    movementC.movement(event, moves, pieces[selectedPieceIndex], pieces, whiteTurn);

                                    selectedPieceBool = false;
                                    if (pieces[selectedPieceIndex].first_move)  pieces[selectedPieceIndex].first_move = false;
                                    moves_counter += 1;
                                    break;
                                
                                case ROOK:
                                    legal_moveC.checkRookMoves(pieces, moves, pieces[selectedPieceIndex]);
                                    movementC.movement(event, moves, pieces[selectedPieceIndex], pieces, whiteTurn);

                                    selectedPieceBool = false;
                                    if (pieces[selectedPieceIndex].first_move)  pieces[selectedPieceIndex].first_move = false;
                                    moves_counter += 1;
                                    break; 
                                
                                case BISHOP:
                                    legal_moveC.checkBishopMoves(pieces, moves, pieces[selectedPieceIndex]);
                                    movementC.movement(event, moves, pieces[selectedPieceIndex], pieces, whiteTurn);

                                    selectedPieceBool = false;
                                    if (pieces[selectedPieceIndex].first_move)  pieces[selectedPieceIndex].first_move = false;
                                    moves_counter += 1;
                                    break;

                                case QUEEN:
                                    vector<pair<float, float>> bishop_moves = queen_moves.first;
                                    vector<pair<float, float>> rook_moves = queen_moves.second;

                                    legal_moveC.checkBishopMoves(pieces, bishop_moves, pieces[selectedPieceIndex]);
                                    legal_moveC.checkRookMoves(pieces, rook_moves, pieces[selectedPieceIndex]);
                                    moves.clear();
                                    moves.insert(moves.end(), bishop_moves.begin(), bishop_moves.end());
                                    moves.insert(moves.end(), rook_moves.begin(), rook_moves.end());

                                    movementC.movement(event, moves, pieces[selectedPieceIndex], pieces, whiteTurn);

                                    selectedPieceBool = false;
                                    if (pieces[selectedPieceIndex].first_move)  pieces[selectedPieceIndex].first_move = false;
                                    moves_counter += 1;
                                    break;
                                    
                            }

                            check_capture(pieces, pieces[selectedPieceIndex]);
                        }
                        
                        break;

                    }
                    
                }

            }

        }  

        Rendering(renderer, pieces, false);

    }                                                                       

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    for(auto texture : pieces) {
        SDL_DestroyTexture(texture.texture);
    }
    SDL_Quit();
} //TODO: inserire requirements.txt