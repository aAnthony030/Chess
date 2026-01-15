#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
//#include <SDL3_mixer/SDL_mixer.h>
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
#include "include/DrawMoves.h"
#include "include/SidebarMoves.h"
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
    whiteRookTexture = IMG_LoadTexture(renderer, "pieces/white-rook.png");
    whitePawnTexture = IMG_LoadTexture(renderer, "pieces/white-pawn.png");
    whiteKingTexture = IMG_LoadTexture(renderer, "pieces/white-king.png");
    whiteQueenTexture = IMG_LoadTexture(renderer, "pieces/white-queen.png");
    whiteBishopTexture = IMG_LoadTexture(renderer, "pieces/white-bishop.png");
    whiteKnightTexture = IMG_LoadTexture(renderer, "pieces/white-knight.png");
    //pezzi neri
    blackRookTexture = IMG_LoadTexture(renderer, "pieces/black-rook.png");
    blackPawnTexture = IMG_LoadTexture(renderer, "pieces/black-pawn.png");
    blackKingTexture = IMG_LoadTexture(renderer, "pieces/black-king.png");
    blackQueenTexture = IMG_LoadTexture(renderer, "pieces/black-queen.png");
    blackBishopTexture = IMG_LoadTexture(renderer, "pieces/black-bishop.png");
    blackKnightTexture = IMG_LoadTexture(renderer, "pieces/black-knight.png");


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
    bool draw_bool = false;
    bool short_castle = false;
    bool long_castle = false;
    bool checkmate = false;
    bool check = false;
    bool promotion = false;
    bool waiting_promotion = false;
    int moves_counter = 1;
    int turn;
    int pieces_number;
    int old_x, old_y;
    char row_chr = '\0';
    char col_chr = '\0';
    char type_chr = '\0';
    vector<string> moves_text;
    
    SDL_Init(SDL_INIT_VIDEO);
    if(!SDL_Init(SDL_INIT_VIDEO) ){
        cerr << "Errore inizializzazione SDL: " << SDL_GetError() << endl;
        return 1;
    }

    window = SDL_CreateWindow("Chess", 840, 640, SDL_WINDOW_RESIZABLE);
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

    TTF_Init();
    if(!TTF_Init()) {
        cerr << "Errore inizializzazione TTF: " << SDL_GetError() << endl;
        return 1;
    }
    
    TTF_Font *font = TTF_OpenFont("C:\\Windows\\Fonts\\arial.ttf", 22);
    if (!font) {
        cerr << "Errore caricamento font: " << SDL_GetError() << endl;
        return 1;
    }
    /*
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cerr << "Errore Mix_OpenAudio: " << Mix_GetError() << endl;
    }

    Mix_Chunk* = movement_sound = Mix_LoadWAV("/sounds/movement_sound.waw");
    Mix_Chunk* = victory = Mix_LoadWAW("/sounds/chess_victory.waw");

    if (!movement_sound || !victory) {
        ceer << "Errore caricamento suoni: " << Mig_GetError() << endl;
    }
    */
    vector<Piece> pieces = PiecesTexture(renderer);
    int selectedPieceIndex;

    while(running){
        while (SDL_PollEvent(&event)) {
        
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }

            else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && !promotion) {
                
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
    
                                        moves = pawnC.pawn_movement(pieces[selectedPieceIndex], pieces);
                                        selectedPieceBool = true;
                                        break;
                                    
                                    case KING:
                                        if (!draw_bool) {
                                            moves = kingC.king_movement(pieces[selectedPieceIndex], pieces, short_castle, long_castle);
    
                                            selectedPieceBool = true;
                                        }
                                        break;
                                    
                                    case KNIGHT:
                                        if (!draw_bool) {
                                            moves = knightC.knight_movement(pieces[selectedPieceIndex]);
    
                                            selectedPieceBool = true;
                                        }
                                        break;
                                
                                    case ROOK:

                                        moves = rookC.rook_movement(pieces[selectedPieceIndex]);

                                        selectedPieceBool = true;
                                        break;  
                                    
                                    case BISHOP:
                                        if (!draw_bool) {
                                            moves = bishopC.bishop_movement(pieces[selectedPieceIndex]);
    
                                            selectedPieceBool = true;
                                        }
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
                                    old_x = pieces[selectedPieceIndex].position.x;
                                    old_y = pieces[selectedPieceIndex].position.y;
                                    pieces_number = pieces.size();
                                    movementC.movement(event, moves, pieces[selectedPieceIndex], pieces, whiteTurn);

                                    int delta_y = abs(old_y - pieces[selectedPieceIndex].position.y);
                                    
                                    for(int p = 0; p < pieces.size(); p++) {
                                        pieces[p].vulnerable_enPassant = false;
                                    }
                                    if (delta_y == 160) {
                                        pieces[selectedPieceIndex].vulnerable_enPassant = true;
                                    }
                                    
                                    selectedPieceBool = false;

                                    if ((pieces[selectedPieceIndex].isWhite && pieces[selectedPieceIndex].position.y <= 0) || (!pieces[selectedPieceIndex].isWhite && 
                                    pieces[selectedPieceIndex].position.y >= 560)) {

                                        row_chr = 'a' + (pieces[selectedPieceIndex].position.x / 80);
                                        col_chr = '8' - (pieces[selectedPieceIndex].position.y / 80);
                                        type_chr;
                                        switch(pieces[selectedPieceIndex].type) {
                                            case BISHOP: type_chr = 'B'; break;
                                            case ROOK: type_chr = 'R'; break;
                                            case KING: type_chr = 'K'; break;
                                            case QUEEN: type_chr = 'Q'; break;
                                            case KNIGHT: type_chr = 'N'; break;
                                        }
                                        waiting_promotion = true;
                                        promotion = true;
                                    }

                                    if (pieces[selectedPieceIndex].first_move)  pieces[selectedPieceIndex].first_move = false;
                                    moves_counter ++;
                                    break;
                                }

                                case KING: {
                                    if (!draw_bool) {
                                        legal_moveC.checkKingMoves(pieces, moves, pieces[selectedPieceIndex]);

                                        old_x = pieces[selectedPieceIndex].position.x;
                                        old_y = pieces[selectedPieceIndex].position.y;
                                        pieces_number = pieces.size();
                                        movementC.movement(event, moves, pieces[selectedPieceIndex], pieces, whiteTurn);

                                        //if (abs(old_x - pieces[selectedPieceIndex].position.x) == 160) long_castle = true;
                                        selectedPieceBool = false;
                                        if (pieces[selectedPieceIndex].first_move)  pieces[selectedPieceIndex].first_move = false;
                                        moves_counter ++;
                                    }


                                    break;

                                }

                                case KNIGHT: {
                                    if (!draw_bool) {
                                        legal_moveC.checkKnightMoves(pieces, moves, pieces[selectedPieceIndex]);

                                        old_x = pieces[selectedPieceIndex].position.x;
                                        old_y = pieces[selectedPieceIndex].position.y;
                                        pieces_number = pieces.size();
                                        movementC.movement(event, moves, pieces[selectedPieceIndex], pieces, whiteTurn);

                                        selectedPieceBool = false;
                                        if (pieces[selectedPieceIndex].first_move)  pieces[selectedPieceIndex].first_move = false;
                                        moves_counter ++;
                                    }


                                    break;
                                
                                }

                                case ROOK: {
                                    legal_moveC.checkRookMoves(pieces, moves, pieces[selectedPieceIndex]);

                                    old_x = pieces[selectedPieceIndex].position.x;
                                    old_y = pieces[selectedPieceIndex].position.y;
                                    pieces_number = pieces.size();
                                    movementC.movement(event, moves, pieces[selectedPieceIndex], pieces, whiteTurn);
                                    selectedPieceBool = false;
                                    if (pieces[selectedPieceIndex].first_move)  pieces[selectedPieceIndex].first_move = false;
                                    moves_counter ++;


                                    break; 
                                
                                }

                                case BISHOP: {
                                    if (!draw_bool) {
                                        legal_moveC.checkBishopMoves(pieces, moves, pieces[selectedPieceIndex]);

                                        old_x = pieces[selectedPieceIndex].position.x;
                                        old_y = pieces[selectedPieceIndex].position.y;
                                        pieces_number = pieces.size();
                                        movementC.movement(event, moves, pieces[selectedPieceIndex], pieces, whiteTurn);

                                        selectedPieceBool = false;
                                        if (pieces[selectedPieceIndex].first_move)  pieces[selectedPieceIndex].first_move = false;
                                        moves_counter ++;
                                    }


                                    break;
                                }

                                case QUEEN: {
                                    vector<pair<float, float>> bishop_moves = queen_moves.first;
                                    vector<pair<float, float>> rook_moves = queen_moves.second;

                                    legal_moveC.checkBishopMoves(pieces, bishop_moves, pieces[selectedPieceIndex]);
                                    legal_moveC.checkRookMoves(pieces, rook_moves, pieces[selectedPieceIndex]);
                                    moves.clear();
                                    moves.insert(moves.end(), bishop_moves.begin(), bishop_moves.end());
                                    moves.insert(moves.end(), rook_moves.begin(), rook_moves.end());

                                    old_x = pieces[selectedPieceIndex].position.x;
                                    old_y = pieces[selectedPieceIndex].position.y;
                                    pieces_number = pieces.size();
                                    movementC.movement(event, moves, pieces[selectedPieceIndex], pieces, whiteTurn);

                                    selectedPieceBool = false;
                                    if (pieces[selectedPieceIndex].first_move)  pieces[selectedPieceIndex].first_move = false;
                                    moves_counter ++;


                                    break;
                                }
                                    
                            }
                            
                            check_capture(pieces, pieces[selectedPieceIndex]);
                            bool piece_eat = (pieces.size() < pieces_number);

                            
                            if (legal_moveC.Checkmate(pieces, whiteTurn)) {
                                checkmate = true;
                                //Mix_PlayChannel(-1, victory, 0);
                            }
                            
                            if (legal_moveC.Stall(pieces, whiteTurn)) {
                                cout << "STALL\n";
                            }
                            
                            if (pieces.size() == 2 && pieces[0].type == KING && pieces[1].type == KING) {
                                cout << "DRAW\n";
                                draw_bool = true;
                            }
                            
                            if (pieces.size() == 3) {
                                int kings = 0;
                                int knight = 0;
                                int bishop = 0;
                                
                                for (int i = 0; i < pieces.size(); i++) {
                                    if (pieces[i].type == KING) {
                                        kings ++;
                                    }
                                    if (pieces[i].type == KNIGHT) {
                                        knight ++;
                                    }
                                    if (pieces[i].type == BISHOP) {
                                        bishop ++;
                                    }
                                    
                                }
                                
                                if (kings == 2 && (bishop == 1 || knight == 1)) {
                                    cout << "DRAW\n";
                                    draw_bool = true;
                                }
                                
                            }
                            if (pieces.size() == 4) {
                                int kings = 0;
                                int knight = 0;
                                int bishop = 0;
                                for (int i = 0; i < pieces.size(); i++) {
                                    if (pieces[i].type == KING) {
                                        kings ++;
                                    }
                                    if (pieces[i].type == KNIGHT) {
                                        knight ++;
                                    }
                                    if (pieces[i].type == BISHOP) {
                                        bishop ++;
                                    }
                                    
                                }
                                
                                if (kings == 2 && (bishop == 2 || knight == 2)) {
                                    cout << "DRAW\n";
                                    draw_bool = true;
                                }
                                
                                turn = moves_counter / 2;
                                
                            }
                            if ((old_x != pieces[selectedPieceIndex].position.x || 
                            old_y != pieces[selectedPieceIndex].position.y)) {
                                MovesHistory({pieces[selectedPieceIndex].position.x, pieces[selectedPieceIndex].position.y}, pieces[selectedPieceIndex].type,
                                moves_text, piece_eat, short_castle, long_castle, check, checkmate, promotion, row_chr, col_chr, type_chr, whiteTurn);

                            }
                            
                        }
                        
                        break;
                        
                    }
                    
                }
                
            }

        }  

        if (promotion) {
            rendering_promote(pieces[selectedPieceIndex], renderer, window, promotion);

            bool piece_eat = (pieces.size() < pieces_number);
            
        }
        else {

            if (selectedPieceBool && selectedPieceIndex >= 0 && selectedPieceIndex <= pieces.size() && moves.size() > 0) {
                DrawMoves(pieces, pieces[selectedPieceIndex], moves, queen_moves, whiteTurn, renderer);
            }
    
            Rendering(renderer, pieces);

        }

        //TODO: sistemare problema promotion e completare sidebar
        // sidebar text
        SDL_Color white = {255, 255, 255, 255};
        int spacing;
        for (int i = 0; i < moves_text.size(); i++) {
            
            SDL_Surface *text_surface = TTF_RenderText_Solid(font, moves_text[i].c_str(), strlen(moves_text[i].c_str()), white);
            spacing = (i * 25);
            if (text_surface) {
                
                SDL_Texture *text_tex = SDL_CreateTextureFromSurface(renderer, text_surface);
                SDL_FRect text_rect = {680, float(45 + spacing), (float)text_surface->w, (float)text_surface->h};
                SDL_DestroySurface(text_surface);
                
                SDL_RenderTexture(renderer, text_tex, NULL, &text_rect);
                SDL_DestroyTexture(text_tex);
            }

        }
            
        string turn_text = whiteTurn ? "Turn: White" : "Turn: Black";
        SDL_Surface *turn_surface = TTF_RenderText_Solid(font, turn_text.c_str(), strlen(turn_text.c_str()), white);
    
        if (turn_surface) {
            SDL_Texture* turn_tex = SDL_CreateTextureFromSurface(renderer, turn_surface);
            SDL_FRect turn_rect = {680, 10, (float)turn_surface->w, (float)turn_surface->h};
            SDL_DestroySurface(turn_surface);
    
            SDL_RenderTexture(renderer, turn_tex, NULL, &turn_rect);
            SDL_DestroyTexture(turn_tex);
        }

        SDL_RenderPresent(renderer);
        
    }                                                                       

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    for(auto texture : pieces) {
        SDL_DestroyTexture(texture.texture);
    }
    TTF_Quit();
    SDL_Quit();
}