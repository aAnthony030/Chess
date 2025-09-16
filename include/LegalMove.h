#pragma once

#include <SDL3/SDL.h>
#include <vector>

template <typename T, typename U, typename V>
class LegalMove {
public:
    void CheckMoves(T& pieces, U moves, V& singoloPiece) {
        int cellsize = 80;

        for (int i = 0; i < moves.size(); i++) {
            bool invalid = false;

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

            // Controllo i pezzi sul board
            for (int j = 0; j < pieces.size(); j++) {
                if (moves[i].first == pieces[j].position.x &&
                    moves[i].second == pieces[j].position.y) {

                    occupied = true;
                    if (pieces[j].isWhite == singoloPiece.isWhite) {
                        occupiedByAlly = true;
                    } else {
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
                i--; // fondamentale per non saltare un elemento
            }

        }

    }

};
