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
                if (moves[i].first < 0 || moves[i].first > 640 ||
                moves[i].second < 0 || moves[i].second > 640) {
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
                    // In diagonale → solo se c'è un nemico
                    if (!occupiedByEnemy) invalid = true;
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
                if (moves[i].first < 0 || moves[i].first > 640 ||
                moves[i].second < 0 || moves[i].second > 640) {
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
                if (moves[i].first < 0 || moves[i].first > 640 ||
                moves[i].second < 0 || moves[i].second > 640) {
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
                 
        }
        

        void checkBishopMoves(T pieces, U& moves, V singoloPiece) {
            const int cellsize = 80;
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
                    moves[i].second == pieces[j].position.y) {
                        
                        pieces_position.push_back({pieces[j].position.x, pieces[j].position.y});
                        
                        if (singoloPiece.isWhite == pieces[j].isWhite) {
                            invalid = true;
                        }
                        
                        break;
                    }
                }
                                
                if (invalid) {
                    moves.erase(moves.begin() + i);
                    i--;
                }

            }

            int selected_piece_x = singoloPiece.position.x;
            int selected_piece_y = singoloPiece.position.y; 
            int delta_pieces_x, delta_pieces_y, delta_move_x, delta_move_y;

            for (int i = 0; i < moves.size(); i++) {
                
                int possible_move_x = moves[i].first;
                int possible_move_y =  moves[i].second;

                for (int j = 0; j < pieces_position.size(); j++) {
                    int non_selected_piece_x = pieces_position[j].first;
                    int non_selected_piece_y = pieces_position[j].second;

                    delta_pieces_x = non_selected_piece_x - selected_piece_x;
                    delta_pieces_y = non_selected_piece_y - selected_piece_y;
                    delta_move_x = possible_move_x - selected_piece_x;
                    delta_move_y = possible_move_y - selected_piece_y;

                    // il pezzo si trova sulla stessa diagonale
                    if (abs(delta_pieces_x) == abs(delta_pieces_y)) {

                        // destra basso (+ +)
                        if (delta_pieces_x > 0 && delta_pieces_y > 0) {
                            if (delta_move_x > delta_pieces_x && delta_move_y > delta_pieces_y) {
                                moves.erase(moves.begin() + i);
                                i--;
                                break;
                            } 

                        }   

                        // sinistra basso (- +)
                        else if (delta_pieces_x < 0 && delta_pieces_y > 0) {
                            if (delta_move_x <delta_pieces_x && delta_move_y > delta_pieces_y) {
                                moves.erase(moves.begin() + i);
                                i--;
                                break;
                            } 

                        }

                        // destra alto (+ -)
                        else if (delta_pieces_x > 0 && delta_pieces_y < 0) {
                            if (delta_move_x > delta_pieces_x && delta_move_y < delta_pieces_y) {
                                moves.erase(moves.begin() + i);
                                i--;
                                break;
                            }     

                        }

                        // sinistra alto (- -)
                        else if(delta_pieces_x < 0 && delta_pieces_y < 0) {
                            if (delta_move_x < delta_pieces_x && delta_move_y < delta_pieces_y) {
                                moves.erase(moves.begin() + i);
                                i--;
                                break;
                            } 

                        }

                    }

                }

            }
            
        }

};