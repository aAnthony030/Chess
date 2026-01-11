#pragma once

#include <vector>
#include "Struct.h"
#include "Piecetypes.h"
#include "LegalMove.h"

using PieceTypes::PAWN;
using PieceTypes::BISHOP;
using PieceTypes::KNIGHT;
using PieceTypes::ROOK;
using PieceTypes::QUEEN;
using PieceTypes::KING;

template <typename T>

void DrawMoves(vector<Piece> pieces, Piece singoloPiece, vector<pair<float, float>> moves, 
pair<vector<pair<float, float>>, vector<pair<float,float>>> queen_moves, bool whiteTurn, T* renderer) {

    if (whiteTurn == singoloPiece.isWhite) {
        LegalMove legal_moveC;
        
        switch (singoloPiece.type) {
            case PAWN: legal_moveC.checkPawnMoves(pieces, moves, singoloPiece); break;
            case KING: legal_moveC.checkKingMoves(pieces, moves, singoloPiece); break;
            case KNIGHT: legal_moveC.checkKnightMoves(pieces, moves, singoloPiece); break;
            case ROOK: legal_moveC.checkRookMoves(pieces, moves, singoloPiece); break;
            case BISHOP: legal_moveC.checkBishopMoves(pieces, moves, singoloPiece); break;
            case QUEEN: 
                vector<pair<float, float>> bishop_moves = queen_moves.first;
                vector<pair<float, float>> rook_moves = queen_moves.second;

                legal_moveC.checkBishopMoves(pieces, bishop_moves, singoloPiece);
                legal_moveC.checkRookMoves(pieces, rook_moves, singoloPiece);
                moves.clear();
                moves.insert(moves.end(), bishop_moves.begin(), bishop_moves.end());
                moves.insert(moves.end(), rook_moves.begin(), rook_moves.end());
                break;

        }

        for (int i = 0; i < pieces.size(); i++) {
            for (int j = 0; j < moves.size(); j++) {
                if (moves[j].first == pieces[i].position.x && moves[j].second == pieces[i].position.y) {
                    const int cellsize = 80;
                    SDL_FRect border = {float(pieces[i].position.x), float(pieces[i].position.y), float(cellsize), float(cellsize)};

                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                    SDL_RenderRect(renderer, &border);
                }

                SDL_FRect dot = {float(moves[j].first + 34), float(moves[j].second + 34), float(12), float(12)};
    
                SDL_SetRenderDrawColor(renderer, 0, 150, 255, 255);
                SDL_RenderFillRect(renderer, &dot);

            }
    
        }

        SDL_RenderPresent(renderer);
    }

}