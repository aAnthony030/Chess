#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include "SpecialMoves.h"
#include "Struct.h"
#include "Pawn.h"
#include "King.h"
#include "Knight.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"

class LegalMove {
    public:

        void checkPawnMoves(vector<Piece> pieces, vector<pair<float,float>>& moves, Piece singoloPiece) {
            const int cellsize = 80;
            bool invalid = false;

            for (int i = moves.size() - 1; i >= 0 ; i--) {
                invalid = false;

                // Controllo che la mossa sia dentro la scacchiera
                if (moves[i].first < 0 || moves[i].first > 560 ||
                moves[i].second < 0 || moves[i].second > 560) {
                    invalid = true;
                }

                if (!invalid) {

                    bool isForward = (moves[i].first == singoloPiece.position.x);
                    bool isDiagonal = (moves[i].first != singoloPiece.position.x);
    
                    bool occupied = false;
                    bool occupiedByEnemy = false;
                    bool occupiedByAlly = false;
    
                    
                    for (int j = 0; j < pieces.size(); j++) {
                        if (moves[i].first == pieces[j].position.x &&
                        moves[i].second == pieces[j].position.y) {
    
                            occupied = true;
                            if (pieces[j].isWhite == singoloPiece.isWhite) {
                                occupiedByAlly = true;
                            } 
                            
                            else {
                                occupiedByEnemy = true;
                            }
    
                            break;
                        }
    
                    }
    
                    // Regole pedoni:
                    if (isForward) {
                        // In avanti → deve essere libera
                        if (occupied) invalid = true;
                    }
    
                    else if (isDiagonal) {
                        // In diagonale solo se c'è un nemico o se è valido l'en passant
                        if (!occupiedByEnemy && !en_passant(singoloPiece, pieces, moves[i]))  {
                            invalid = true;
                        }
    
                    }
    
                    if (!invalid && isMoveLegal(singoloPiece, pieces, moves[i])) {
                        invalid = true;
                    }

                }

                if (invalid) {
                    moves.erase(moves.begin() + i);
                }

            }

        }


        void checkKingMoves(vector<Piece> pieces, vector<pair<float,float>>& moves, Piece singoloPiece) {
            const int cellsize = 80;
            bool invalid = false;

            for (int i = moves.size() - 1; i >= 0 ; i--) {
                invalid = false;

                // Controllo che la mossa sia dentro la scacchiera
                if (moves[i].first < 0 || moves[i].first > 560 ||
                moves[i].second < 0 || moves[i].second > 560) {
                    invalid = true;
                }

                if (!invalid) {

                    for(int j = 0; j < pieces.size(); j++) {
    
                        if (moves[i].first == pieces[j].position.x && 
                        moves[i].second == pieces[j].position.y && singoloPiece.isWhite == pieces[j].isWhite) {
                            invalid = true;
                            break;
                        }
    
                    }
                    
                    if (!invalid && isMoveLegal(singoloPiece, pieces, moves[i])) {
                        invalid = true;
                    }

                }
                

                if (invalid) {
                    moves.erase(moves.begin() + i);
                }

            }

        }


        void checkKnightMoves(vector<Piece> pieces, vector<pair<float,float>>& moves, Piece singoloPiece) {
            
            const int cellsize = 80;
            bool invalid = false;

            for (int i = moves.size() - 1; i >= 0 ; i--) {
                invalid = false;

                // Controllo che la mossa sia dentro la scacchiera
                if (moves[i].first < 0 || moves[i].first > 560 ||
                moves[i].second < 0 || moves[i].second > 560) {
                    invalid = true;
                }

                if (!invalid) {

                    for(int j = 0; j < pieces.size(); j++) {
    
                        if (moves[i].first == pieces[j].position.x && 
                        moves[i].second == pieces[j].position.y && singoloPiece.isWhite == pieces[j].isWhite) {
                            invalid = true;
                            break;
                        }
    
                    }
    
                    if (!invalid && isMoveLegal(singoloPiece, pieces, moves[i])) {
                        invalid = true;
                    }

                }

                if (invalid) {
                    moves.erase(moves.begin() + i);
                }

            }

        }   


        void checkRookMoves(vector<Piece> pieces, vector<pair<float,float>>& moves, Piece singoloPiece) {
            
            const int cellsize = 80;
            vector<pair<float, float>> dx_moves;
            vector<pair<float, float>> sx_moves;
            vector<pair<float, float>> up_moves;
            vector<pair<float, float>> down_moves;

            for (int i = moves.size() - 1; i >= 0 ; i--) {

                if (moves[i].first < 0 || moves[i].first > 560 ||
                moves[i].second < 0 || moves[i].second > 560) {

                    moves.erase(moves.begin() + i);
                    continue;
                }

                if (moves[i].first == singoloPiece.position.x) {
                    
                    if (moves[i].second > singoloPiece.position.y) {
                        down_moves.push_back({moves[i].first, moves[i].second});
                        continue;
                    }

                    up_moves.push_back({moves[i].first, moves[i].second});

                }

                if (moves[i].second == singoloPiece.position.y) {

                    if (moves[i].first > singoloPiece.position.x) {
                        dx_moves.push_back({moves[i].first, moves[i].second});
                        continue;
                    }

                    sx_moves.push_back({moves[i].first, moves[i].second});

                }

            }
            // uso reverse in quanto nel ciclo itero moves partendo dall'ultimo elemento
            reverse(dx_moves.begin(), dx_moves.end());
            reverse(sx_moves.begin(), sx_moves.end());
            reverse(up_moves.begin(), up_moves.end());
            reverse(down_moves.begin(), down_moves.end());

            // mosse su
            for (int i = 0; i < up_moves.size() ; i++) {

                for (int j = 0; j < pieces.size(); j++) {

                    if (pieces[j].position.x == up_moves[i].first && pieces[j].position.y == up_moves[i].second) {

                        if (pieces[j].isWhite == singoloPiece.isWhite) {
                            up_moves.erase(up_moves.begin() + i, up_moves.end());
                        }

                        else {
                            up_moves.erase(up_moves.begin() + i + 1, up_moves.end());
                        }

                        break;

                    }

                }

            }

            // mosse giù
            for (int i = 0; i < down_moves.size() ; i++) {

                for (int j = 0; j < pieces.size(); j++) {

                    if (pieces[j].position.x == down_moves[i].first && pieces[j].position.y == down_moves[i].second) {

                        if (pieces[j].isWhite == singoloPiece.isWhite) {
                            down_moves.erase(down_moves.begin() + i, down_moves.end());
                        }

                        else {
                            down_moves.erase(down_moves.begin() + i + 1, down_moves.end());
                        }

                        break;

                    }

                }

            }

            // mosse destra
            for (int i = 0; i < dx_moves.size() ; i++) {

                for (int j = 0; j < pieces.size(); j++) {

                    if (pieces[j].position.x == dx_moves[i].first && pieces[j].position.y == dx_moves[i].second) {

                        if (pieces[j].isWhite == singoloPiece.isWhite) {
                            dx_moves.erase(dx_moves.begin() + i, dx_moves.end());
                        }

                        else {
                            dx_moves.erase(dx_moves.begin() + i + 1, dx_moves.end());
                        }

                        break;

                    }

                }
            
            }

            // mosse sinistra
            for (int i = 0; i < sx_moves.size() ; i++) {

                for (int j = 0; j < pieces.size(); j++) {

                    if (pieces[j].position.x == sx_moves[i].first && pieces[j].position.y == sx_moves[i].second) {

                        if (pieces[j].isWhite == singoloPiece.isWhite) {
                            sx_moves.erase(sx_moves.begin() + i, sx_moves.end());
                        }

                        else {
                            sx_moves.erase(sx_moves.begin() + i + 1, sx_moves.end());
                        }

                        break;

                    }

                }
        
            }

            moves.clear();
            moves.insert(moves.end(), up_moves.begin(),   up_moves.end());
            moves.insert(moves.end(), down_moves.begin(), down_moves.end());
            moves.insert(moves.end(), dx_moves.begin(),   dx_moves.end());
            moves.insert(moves.end(), sx_moves.begin(),   sx_moves.end());

            for (int i = moves.size() - 1; i >= 0; i--) {
                
                if (isMoveLegal(singoloPiece, pieces, moves[i])) {
                    moves.erase(moves.begin() + i);
                }

            }

        }


        void checkBishopMoves(vector<Piece> pieces, vector<pair<float,float>>& moves, Piece singoloPiece) {

            const int cellsize = 80;
            vector<pair<float, float>> upr_moves; // up - right
            vector<pair<float, float>> upl_moves; // up - left
            vector<pair<float, float>> downr_moves; // down - right
            vector<pair<float, float>> downl_moves; // down - left

            for (int i = moves.size() - 1; i >= 0 ; i--) {

                if (moves[i].first < 0 || moves[i].first > 560 ||
                moves[i].second < 0 || moves[i].second > 560) {

                    moves.erase(moves.begin() + i);
                    continue;
                }

                if (moves[i].first > singoloPiece.position.x && moves[i].second > singoloPiece.position.y) {
                    downr_moves.push_back({moves[i].first, moves[i].second});
                    continue;
                }

                if (moves[i].first < singoloPiece.position.x && moves[i].second > singoloPiece.position.y) {
                    downl_moves.push_back({moves[i].first, moves[i].second});
                    continue;
                }

                if (moves[i].first > singoloPiece.position.x && moves[i].second < singoloPiece.position.y) {
                    upr_moves.push_back({moves[i].first, moves[i].second});
                    continue;
                }

                if (moves[i].first < singoloPiece.position.x && moves[i].second < singoloPiece.position.y) {
                    upl_moves.push_back({moves[i].first, moves[i].second});
                    continue;
                }

            }

            // uso reverse in quanto nel ciclo itero moves partendo dall'ultimo elemento
            reverse(upr_moves.begin(), upr_moves.end());
            reverse(upl_moves.begin(), upl_moves.end());
            reverse(downr_moves.begin(), downr_moves.end());
            reverse(downl_moves.begin(), downl_moves.end());
            
            // up - right
            for (int i = 0; i < upr_moves.size(); i++) {

                for (int j = 0; j < pieces.size(); j++) { 

                    if (upr_moves[i].first == pieces[j].position.x && upr_moves[i].second == pieces[j].position.y) {

                        if (pieces[j].isWhite == singoloPiece.isWhite) {
                            upr_moves.erase(upr_moves.begin() + i, upr_moves.end());
                        }

                        else {
                            upr_moves.erase(upr_moves.begin() + i + 1, upr_moves.end());
                        }

                        break;

                    }

                }

            }

            // up - left
            for (int i = 0; i < upl_moves.size(); i++) {

                for (int j = 0; j < pieces.size(); j++) { 

                    if (upl_moves[i].first == pieces[j].position.x && upl_moves[i].second == pieces[j].position.y) {

                        if (pieces[j].isWhite == singoloPiece.isWhite) {
                            upl_moves.erase(upl_moves.begin() + i, upl_moves.end());
                        }

                        else {
                            upl_moves.erase(upl_moves.begin() + i + 1, upl_moves.end());
                        }

                        break;

                    }

                }

            }

            // down - right
            for (int i = 0; i < downr_moves.size(); i++) {

                for (int j = 0; j < pieces.size(); j++) { 

                    if (downr_moves[i].first == pieces[j].position.x && downr_moves[i].second == pieces[j].position.y) {

                        if (pieces[j].isWhite == singoloPiece.isWhite) {
                            downr_moves.erase(downr_moves.begin() + i, downr_moves.end());
                        }

                        else {
                            downr_moves.erase(downr_moves.begin() + i + 1, downr_moves.end());
                        }

                        break;

                    }

                }

            }

            // down - left
            for (int i = 0; i < downl_moves.size(); i++) {

                for (int j = 0; j < pieces.size(); j++) { 

                    if (downl_moves[i].first == pieces[j].position.x && downl_moves[i].second == pieces[j].position.y) {

                        if (pieces[j].isWhite == singoloPiece.isWhite) {
                            downl_moves.erase(downl_moves.begin() + i, downl_moves.end());
                        }

                        else {
                            downl_moves.erase(downl_moves.begin() + i + 1, downl_moves.end());
                        }

                        break;

                    }

                }

            }    

            moves.clear();
            moves.insert(moves.end(), upr_moves.begin(),   upr_moves.end());
            moves.insert(moves.end(), upl_moves.begin(), upl_moves.end());
            moves.insert(moves.end(), downr_moves.begin(),   downr_moves.end());
            moves.insert(moves.end(), downl_moves.begin(),   downl_moves.end());

            for (int i = moves.size() - 1; i >= 0; i--) {

                if (isMoveLegal(singoloPiece, pieces, moves[i])) {
                    moves.erase(moves.begin() + i);
                }

            }

        }

      
        void checkRookMovesNoCheck(vector<Piece> pieces, vector<pair<float,float>>& moves, Piece singoloPiece) {
            
            const int cellsize = 80;
            vector<pair<float, float>> dx_moves;
            vector<pair<float, float>> sx_moves;
            vector<pair<float, float>> up_moves;
            vector<pair<float, float>> down_moves;

            for (int i = moves.size() - 1; i >= 0 ; i--) {

                if (moves[i].first < 0 || moves[i].first > 560 ||
                moves[i].second < 0 || moves[i].second > 560) {

                    moves.erase(moves.begin() + i);
                    continue;
                }

                if (moves[i].first == singoloPiece.position.x) {
                    
                    if (moves[i].second > singoloPiece.position.y) {
                        down_moves.push_back({moves[i].first, moves[i].second});
                        continue;
                    }

                    up_moves.push_back({moves[i].first, moves[i].second});

                }

                if (moves[i].second == singoloPiece.position.y) {

                    if (moves[i].first > singoloPiece.position.x) {
                        dx_moves.push_back({moves[i].first, moves[i].second});
                        continue;
                    }

                    sx_moves.push_back({moves[i].first, moves[i].second});

                }

            }
            // uso reverse in quanto nel ciclo itero moves partendo dall'ultimo elemento
            reverse(dx_moves.begin(), dx_moves.end());
            reverse(sx_moves.begin(), sx_moves.end());
            reverse(up_moves.begin(), up_moves.end());
            reverse(down_moves.begin(), down_moves.end());

            // mosse su
            for (int i = 0; i < up_moves.size() ; i++) {

                for (int j = 0; j < pieces.size(); j++) {

                    if (pieces[j].position.x == up_moves[i].first && pieces[j].position.y == up_moves[i].second) {

                        if (pieces[j].isWhite == singoloPiece.isWhite) {
                            up_moves.erase(up_moves.begin() + i, up_moves.end());
                        }

                        else {
                            up_moves.erase(up_moves.begin() + i + 1, up_moves.end());
                        }

                        break;

                    }

                }

            }

            // mosse giù
            for (int i = 0; i < down_moves.size() ; i++) {

                for (int j = 0; j < pieces.size(); j++) {

                    if (pieces[j].position.x == down_moves[i].first && pieces[j].position.y == down_moves[i].second) {

                        if (pieces[j].isWhite == singoloPiece.isWhite) {
                            down_moves.erase(down_moves.begin() + i, down_moves.end());
                        }

                        else {
                            down_moves.erase(down_moves.begin() + i + 1, down_moves.end());
                        }

                        break;

                    }

                }

            }

            // mosse destra
            for (int i = 0; i < dx_moves.size() ; i++) {

                for (int j = 0; j < pieces.size(); j++) {

                    if (pieces[j].position.x == dx_moves[i].first && pieces[j].position.y == dx_moves[i].second) {

                        if (pieces[j].isWhite == singoloPiece.isWhite) {
                            dx_moves.erase(dx_moves.begin() + i, dx_moves.end());
                        }

                        else {
                            dx_moves.erase(dx_moves.begin() + i + 1, dx_moves.end());
                        }

                        break;

                    }

                }
            
            }

            // mosse sinistra
            for (int i = 0; i < sx_moves.size() ; i++) {

                for (int j = 0; j < pieces.size(); j++) {

                    if (pieces[j].position.x == sx_moves[i].first && pieces[j].position.y == sx_moves[i].second) {

                        if (pieces[j].isWhite == singoloPiece.isWhite) {
                            sx_moves.erase(sx_moves.begin() + i, sx_moves.end());
                        }

                        else {
                            sx_moves.erase(sx_moves.begin() + i + 1, sx_moves.end());
                        }

                        break;

                    }

                }
        
            }

            moves.clear();
            moves.insert(moves.end(), up_moves.begin(),   up_moves.end());
            moves.insert(moves.end(), down_moves.begin(), down_moves.end());
            moves.insert(moves.end(), dx_moves.begin(),   dx_moves.end());
            moves.insert(moves.end(), sx_moves.begin(),   sx_moves.end());

        }


        void checkBishopMovesNoCheck(vector<Piece> pieces, vector<pair<float,float>>& moves, Piece singoloPiece) {

            const int cellsize = 80;
            vector<pair<float, float>> upr_moves; // up - right
            vector<pair<float, float>> upl_moves; // up - left
            vector<pair<float, float>> downr_moves; // down - right
            vector<pair<float, float>> downl_moves; // down - left

            for (int i = moves.size() - 1; i >= 0 ; i--) {

                if (moves[i].first < 0 || moves[i].first > 560 ||
                moves[i].second < 0 || moves[i].second > 560) {

                    moves.erase(moves.begin() + i);
                    continue;
                }

                if (moves[i].first > singoloPiece.position.x && moves[i].second > singoloPiece.position.y) {
                    downr_moves.push_back({moves[i].first, moves[i].second});
                    continue;
                }

                if (moves[i].first < singoloPiece.position.x && moves[i].second > singoloPiece.position.y) {
                    downl_moves.push_back({moves[i].first, moves[i].second});
                    continue;
                }

                if (moves[i].first > singoloPiece.position.x && moves[i].second < singoloPiece.position.y) {
                    upr_moves.push_back({moves[i].first, moves[i].second});
                    continue;
                }

                if (moves[i].first < singoloPiece.position.x && moves[i].second < singoloPiece.position.y) {
                    upl_moves.push_back({moves[i].first, moves[i].second});
                    continue;
                }

            }

            // uso reverse in quanto nel ciclo itero moves partendo dall'ultimo elemento
            reverse(upr_moves.begin(), upr_moves.end());
            reverse(upl_moves.begin(), upl_moves.end());
            reverse(downr_moves.begin(), downr_moves.end());
            reverse(downl_moves.begin(), downl_moves.end());
            
            // up - right
            for (int i = 0; i < upr_moves.size(); i++) {

                for (int j = 0; j < pieces.size(); j++) { 

                    if (upr_moves[i].first == pieces[j].position.x && upr_moves[i].second == pieces[j].position.y) {

                        if (pieces[j].isWhite == singoloPiece.isWhite) {
                            upr_moves.erase(upr_moves.begin() + i, upr_moves.end());
                        }

                        else {
                            upr_moves.erase(upr_moves.begin() + i + 1, upr_moves.end());
                        }

                        break;

                    }

                }

            }

            // up - left
            for (int i = 0; i < upl_moves.size(); i++) {

                for (int j = 0; j < pieces.size(); j++) { 

                    if (upl_moves[i].first == pieces[j].position.x && upl_moves[i].second == pieces[j].position.y) {

                        if (pieces[j].isWhite == singoloPiece.isWhite) {
                            upl_moves.erase(upl_moves.begin() + i, upl_moves.end());
                        }

                        else {
                            upl_moves.erase(upl_moves.begin() + i + 1, upl_moves.end());
                        }

                        break;

                    }

                }

            }

            // down - right
            for (int i = 0; i < downr_moves.size(); i++) {

                for (int j = 0; j < pieces.size(); j++) { 

                    if (downr_moves[i].first == pieces[j].position.x && downr_moves[i].second == pieces[j].position.y) {

                        if (pieces[j].isWhite == singoloPiece.isWhite) {
                            downr_moves.erase(downr_moves.begin() + i, downr_moves.end());
                        }

                        else {
                            downr_moves.erase(downr_moves.begin() + i + 1, downr_moves.end());
                        }

                        break;

                    }

                }

            }

            // down - left
            for (int i = 0; i < downl_moves.size(); i++) {

                for (int j = 0; j < pieces.size(); j++) { 

                    if (downl_moves[i].first == pieces[j].position.x && downl_moves[i].second == pieces[j].position.y) {

                        if (pieces[j].isWhite == singoloPiece.isWhite) {
                            downl_moves.erase(downl_moves.begin() + i, downl_moves.end());
                        }

                        else {
                            downl_moves.erase(downl_moves.begin() + i + 1, downl_moves.end());
                        }

                        break;

                    }

                }

            }    

            moves.clear();
            moves.insert(moves.end(), upr_moves.begin(),   upr_moves.end());
            moves.insert(moves.end(), upl_moves.begin(), upl_moves.end());
            moves.insert(moves.end(), downr_moves.begin(),   downr_moves.end());
            moves.insert(moves.end(), downl_moves.begin(),   downl_moves.end());

        }

        // EX endgame

        bool Check(vector<Piece>& pieces, bool whiteTurn) {

            Pawn pawnC;
            King  kingC;
            Knight knightC;
            Rook rookC;
            Bishop bishopC;
            Queen queenC;
            vector <pair<float,float>> moves;
            const int cellsize = 80;
            float x, y;

            int king_index = -1;
            for (int i = 0; i < pieces.size(); i++) {
                if (pieces[i].type == KING && pieces[i].isWhite == whiteTurn) {
                    king_index = i;
                    break;
                }

            } 

            if (king_index == -1) return false;

            for (int i = 0; i < pieces.size(); i++) {

                if (pieces[i].isWhite != pieces[king_index].isWhite) {
                    switch (pieces[i].type) {
                                            
                        case PAWN:
            
                            moves = pawnC.pawn_movement(pieces[i]);
                            break;
                                            
                        case KING:

                            moves = kingC.king_movement(pieces[i], pieces);
                            break;
                                            
                        case KNIGHT:

                            moves = knightC.knight_movement(pieces[i]);
                            break;
                                        
                        case ROOK:

                            moves = rookC.rook_movement(pieces[i]);

                            break;  
                                            
                        case BISHOP:

                            moves = bishopC.bishop_movement(pieces[i]);

                            break;  
                                            
                        case QUEEN:

                            pair<vector<pair<float, float>>, vector<pair<float, float>>> queen_moves = queenC.queen_movement(pieces[i]);
            
                            vector<pair<float, float>> bishop_moves = queen_moves.first;
                            vector<pair<float, float>> rook_moves = queen_moves.second;

                            checkRookMovesNoCheck(pieces, rook_moves, pieces[i]);
                            checkBishopMovesNoCheck(pieces, bishop_moves, pieces[i]);

                            moves.clear();
                            moves.insert(moves.end(), bishop_moves.begin(), bishop_moves.end());
                            moves.insert(moves.end(), rook_moves.begin(), rook_moves.end());
                            break; 

                    }

                    for (int j = 0; j < moves.size(); j++) {
                        if (moves[j].first == pieces[king_index].position.x && moves[j].second == pieces[king_index].position.y) {
                            return true;
                        }

                    }

                }

            }

            return false;

        }
        // simulo la scacchiera per testare ogni possibile mossa e vedere se protegge il re
        bool isMoveLegal(Piece singoloPiece, vector<Piece> pieces, pair<float,float> move) {
            for (int i = 0; i < pieces.size(); i++) {

                if (pieces[i].position.x == singoloPiece.position.x && 
                pieces[i].position.y == singoloPiece.position.y &&
                pieces[i].isWhite == singoloPiece.isWhite) {

                    pieces[i].position.x = move.first;
                    pieces[i].position.y = move.second;
                    break;
                }

            }

            return Check(pieces, singoloPiece.isWhite);

        }

        void Checkmate() {
            // TODO
        }

        void Stall() {
            // TODO
        }

};