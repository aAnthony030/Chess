#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <cmath>

template <typename T, typename U, typename V>

class LegalMove {
    public:

        void checkPawnMoves(T pieces, U& moves, V singoloPiece) {
            const int cellsize = 80;
            bool invalid = false;

            for (int i = 0; i < moves.size(); i++) {
                invalid = false;

                // Controllo che la mossa sia dentro la scacchiera
                if (moves[i].first < 0 || moves[i].first > 560 ||
                moves[i].second < 0 || moves[i].second > 560) {
                    invalid = true;
                }

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

                if (invalid) {
                    moves.erase(moves.begin() + i);
                    i--;    
                }

            }

        }


        void checkKingMoves(T pieces, U& moves, V singoloPiece) {
            const int cellsize = 80;
            bool invalid = false;

            for (int i = 0; i < moves.size(); i++) {
                invalid = false;

                // Controllo che la mossa sia dentro la scacchiera
                if (moves[i].first < 0 || moves[i].first > 560 ||
                moves[i].second < 0 || moves[i].second > 560) {
                    invalid = true;
                }


                for(int j = 0; j < pieces.size(); j++) {

                    if (moves[i].first == pieces[j].position.x && 
                    moves[i].second == pieces[j].position.y && singoloPiece.isWhite == pieces[j].isWhite) {
                        invalid = true;
                        break;
                    }

                }
                
                if (invalid) {
                    moves.erase(moves.begin() + i);
                    i--;
                }

            }

        }


        void checkKnightMoves(T pieces, U& moves, V singoloPiece) {
            
            const int cellsize = 80;
            bool invalid = false;

            for (int i = 0; i < moves.size(); i++) {
                invalid = false;

                // Controllo che la mossa sia dentro la scacchiera
                if (moves[i].first < 0 || moves[i].first > 560 ||
                moves[i].second < 0 || moves[i].second > 560) {
                    invalid = true;
                }

                for(int j = 0; j < pieces.size(); j++) {

                    if (moves[i].first == pieces[j].position.x && 
                    moves[i].second == pieces[j].position.y && singoloPiece.isWhite == pieces[j].isWhite) {
                        invalid = true;
                        break;
                    }

                }
                
                if (invalid) {
                    moves.erase(moves.begin() + i);
                    i--;
                }

            }

        }   


        void checkRookMoves(T pieces, U& moves, V singoloPiece) {
            
            const int cellsize = 80;
            int directions[4][2] = {
                { int(singoloPiece.position.x), -cellsize },  // su
                { int(singoloPiece.position.x), cellsize },  // giu
                { -cellsize, int(singoloPiece.position.y) },  // sinistra
                { cellsize, int(singoloPiece.position.y) }   // destra
            };

            for (int i = 0; i < 4; i++) {

                int dir_x = directions[i][0];
                int dir_y = directions[i][1];

                // controllo movimento asse x
                int move_x = singoloPiece.position.x + dir_x;
                while (move_x >= 0 && move_x <= 560) {
    
                    bool occupied = false;

                    for (int j = 0; j < pieces.size(); j++) {
                        // controllo sulle caselle per vedere se ci sono pezzi
                        if (pieces[j].position.x == move_x && pieces[j].position.y == singoloPiece.position.y) {

                            occupied = true;

                            if (pieces[j].isWhite != singoloPiece.isWhite) {
                                moves.push_back({move_x, singoloPiece.position.y});
                            }

                            break;  // fine direzione
                        }

                    }

                    // se c'è un pezzo bianco fine direzione
                    if (occupied) {
                        break;
                    }

                    // casella libera
                    moves.push_back({move_x, singoloPiece.position.y});

                    move_x += dir_x;

                }
                
                // controllo movimento asse y
                int move_y = singoloPiece.position.y + dir_y;
                while (move_y >= 0 && move_y <= 560) {
    
                    bool occupied = false;

                    for (int j = 0; j < pieces.size(); j++) {
                        // controllo sulle caselle per vedere se ci sono pezzi
                        if (pieces[j].position.x == singoloPiece.position.x && pieces[j].position.y == move_y) {

                            occupied = true;

                            if (pieces[j].isWhite != singoloPiece.isWhite) {
                                moves.push_back({singoloPiece.position.x, move_y});
                            }

                            break;  // fine direzione
                        }

                    }

                    // se c'è un pezzo bianco fine direzione
                    if (occupied) {
                        break;
                    }

                    // casella libera
                    moves.push_back({singoloPiece.position.x, move_y});

                    move_y += dir_y; 

                }
            }

            /*
            bool invalid;
            vector<pair<float, float>> pieces_position;
            
            for (int i = 0; i < moves.size(); i++) {

                bool isForward = (moves[i].first == singoloPiece.position.x);
                invalid = false;
                
                // Controllo che la mossa sia dentro la scacchiera
                if (moves[i].first < 0 || moves[i].first > 640 ||
                moves[i].second < 0 || moves[i].second > 640) {
                    invalid = true;
                }

                
                for(int j = 0; j < pieces.size(); j++) {

                if (moves[i].first == pieces[j].position.x && 
                moves[i].second == pieces[j].position.y && singoloPiece.isWhite == pieces[j].isWhite) {
                    invalid = true;
                    pieces_position.push_back({pieces[j].position.x, pieces[j].position.y});
                    break;
                }
                // !
                else if (moves[i].first == pieces[j].position.x && 
                moves[i].second == pieces[j].position.y && singoloPiece.isWhite != pieces[j].isWhite) {
                        pieces_position.push_back({pieces[j].position.x, pieces[j].position.y});
                    }

                }
                
                if (invalid) {
                    moves.erase(moves.begin() + i);
                    i--;
                }

            }

            int selected_piece_x = singoloPiece.position.x;
            int selected_piece_y = singoloPiece.position.y; 
            
            for (int i = 0; i < moves.size(); i++) {
                
            int possible_move_x = moves[i].first;
            int possible_move_y =  moves[i].second;
            
            for (int j = 0; j < pieces_position.size(); j++) {
                int non_selected_piece_x = pieces_position[j].first;
                int non_selected_piece_y = pieces_position[j].second;

                    // il pezzo è sulla stessa Y, si lavora sulla X
                    if (selected_piece_y == non_selected_piece_y) {   
                        
                    int dist_move_piece = possible_move_x - selected_piece_x;
                    int dist_nonSelectedPiece_piece = non_selected_piece_x - selected_piece_x;
                    
                    if (abs(dist_nonSelectedPiece_piece) < abs(dist_move_piece)) {
                        moves.erase(moves.begin() + i);
                        i--;
                        break;
                    }
                    
                }
                
                // il pezzo è sulla stessa X, si lavora sulla Y
                    else if (selected_piece_x == non_selected_piece_x) {
                        
                    int dist_move_piece = possible_move_y - selected_piece_y;
                    int dist_nonSelectedPiece_piece = non_selected_piece_y - selected_piece_y;
                    
                    if (abs(dist_nonSelectedPiece_piece) < abs(dist_move_piece)) {
                        moves.erase(moves.begin() + i);
                        i--;
                        break;
                    }
                    
                }
                
            }
            
        }
        */
    }
      

        void checkBishopMoves(T pieces, U& moves, V singoloPiece) {

            const int cellsize = 80;
            int directions[4][2] = {
                { cellsize, cellsize },  // basso a destra (+ +)
                { cellsize, -cellsize },  // alto a destra (+ -)
                { -cellsize, cellsize },  // basso a sinistra (- +)
                { -cellsize, -cellsize }   // alto a sinistra (- -)
            };

            for (int i = 0; i < 4; i++) {

                int dir_x = directions[i][0];
                int dir_y = directions[i][1];

                int move_x = singoloPiece.position.x + dir_x;
                int move_y = singoloPiece.position.y + dir_y;

                while (move_x >= 0 && move_x <= 560 && move_y >= 0 && move_y <= 560) {

                    bool occupied = false;

                    for (int j = 0; j < pieces.size(); j++) {
                        // controllo sulle caselle per vedere se ci sono pezzi
                        if (pieces[j].position.x == move_x && pieces[j].position.y == move_y) {

                            occupied = true;

                            if (pieces[j].isWhite != singoloPiece.isWhite) {
                                moves.push_back({move_x, move_y});
                            }

                            break;  // fine direzione
                        }

                    }

                    // se c'è un pezzo bianco fine direzione
                    if (occupied) {
                        break;
                    }

                    // casella libera
                    moves.push_back({move_x, move_y});

                    move_x += dir_x;
                    move_y += dir_y;
                }
    
            }
            
        }

};