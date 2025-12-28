#ifndef PIECE_H
#define PIECE_H

#pragma once

struct Piece {
    SDL_Texture* texture;
    bool isWhite;
    enum PieceTypes type;
    SDL_FRect position;
    bool alive = true;
    bool first_move = true;
    bool vulnerable_enPassant = false;
};

#endif