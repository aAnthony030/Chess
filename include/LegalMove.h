#ifndef LEGALMOVE_H
#define LEGALMOVE_H

#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <cmath>
#include "SpecialMoves.h"
#include "EndGame.h"
#include "Struct.h"

class LegalMove {
    public:

        void checkPawnMoves(vector<Piece> pieces, vector<pair<float,float>>& moves, Piece singoloPiece, bool is_called_from_endGame) {
            const int cellsize = 80;
            bool invalid = false;

            for (int i = moves.size() - 1; i >= 0 ; i--) {
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

                if (!invalid && isMoveLegal(singoloPiece, pieces, moves[i])) {
                    invalid = true;
                }

                if (invalid) {
                    moves.erase(moves.begin() + i);
                }

            }

        }


        void checkKingMoves(vector<Piece> pieces, vector<pair<float,float>>& moves, Piece singoloPiece, bool is_called_from_endGame) {
            const int cellsize = 80;
            bool invalid = false;

            for (int i = moves.size() - 1; i >= 0 ; i--) {
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
                
                if (!invalid && isMoveLegal(singoloPiece, pieces, moves[i])) {
                    invalid = true;
                }

                if (invalid) {
                    moves.erase(moves.begin() + i);
                }

            }

        }


        void checkKnightMoves(vector<Piece> pieces, vector<pair<float,float>>& moves, Piece singoloPiece, bool is_called_from_endGame) {
            
            const int cellsize = 80;
            bool invalid = false;

            for (int i = moves.size() - 1; i >= 0 ; i--) {
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

                if (!invalid && isMoveLegal(singoloPiece, pieces, moves[i])) {
                    invalid = true;
                }

                if (invalid) {
                    moves.erase(moves.begin() + i);
                }

            }

        }   


        void checkRookMoves(vector<Piece> pieces, vector<pair<float,float>>& moves, Piece singoloPiece, bool is_called_from_endGame) {
            
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

            if (is_called_from_endGame) {
                for(int i = moves.size() - 1; i >= 0; i--) {

                    if (!isMoveLegal(singoloPiece, pieces, moves[i])) {
                        moves.erase(moves.begin() + i);
                    }

                }

            }
        
        }

      

        void checkBishopMoves(vector<Piece> pieces, vector<pair<float,float>>& moves, Piece singoloPiece, bool is_called_from_endGame) {

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

            if (is_called_from_endGame) {
                for(int i = moves.size() - 1; i >= 0; i--) {
                    
                    if (!isMoveLegal(singoloPiece, pieces, moves[i])) {
                        moves.erase(moves.begin() + i);
                    }

                }

            }
            
        }

};

#endif