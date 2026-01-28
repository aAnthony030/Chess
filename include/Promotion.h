#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <utility>
#include "Piecetypes.h"
#include "Rendering.h"
#include "Struct.h"

using PieceTypes::PAWN;
using PieceTypes::BISHOP;
using PieceTypes::KNIGHT;
using PieceTypes::ROOK;
using PieceTypes::QUEEN;
using PieceTypes::KING;

// se si prova a chiudere il programma quando è in fase di selezione non viene permesso
void rendering_promote(Piece& piece, SDL_Renderer* renderer, SDL_Window* window, bool& promotion, enum PieceTypes& promotionPieceType) {
    const int cellsize = 80;
    std::cout << "sono dentro rendering_promote\n";
    SDL_Texture* textures[4] = {
        piece.isWhite ? IMG_LoadTexture(renderer, "pieces/white-rook.png") : IMG_LoadTexture(renderer, "pieces/black-rook.png"),
        piece.isWhite ? IMG_LoadTexture(renderer, "pieces/white-queen.png") : IMG_LoadTexture(renderer, "pieces/black-queen.png"),
        piece.isWhite ? IMG_LoadTexture(renderer, "pieces/white-bishop.png") : IMG_LoadTexture(renderer, "pieces/black-bishop.png"),
        piece.isWhite ? IMG_LoadTexture(renderer, "pieces/white-knight.png") : IMG_LoadTexture(renderer, "pieces/black-knight.png")
    };

    SDL_SetRenderDrawColor(renderer, 240, 217, 181, 255); // casella chiaro
    SDL_RenderClear(renderer);

    for (int i = 0; i < 4; i++) {
        SDL_FRect cordinate = {float(i*cellsize), float(0), float(cellsize), float(cellsize) };
        SDL_RenderTexture(renderer, textures[i], nullptr, &cordinate);
    }
    
    SDL_RenderPresent(renderer);
    std::cout << "SDL_RenderPresent attivo\n";
    SDL_Event event;
    bool chosen = false;
    while (!chosen) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                int x = event.button.x;
                int y = event.button.y;

                for (int i = 0; i < 4; i++) {
                    SDL_FRect cordinate = { float(i*cellsize), float(0), float(cellsize), float(cellsize)};

                    if (x >= cordinate.x && x <= cordinate.x + cordinate.w && y >= cordinate.y && y <= cordinate.y + cordinate.h) {

                        switch (i) {

                            case 0:
                                piece.type = ROOK;
                                promotionPieceType = ROOK;
                                break;

                            case 1:
                                piece.type = QUEEN;
                                promotionPieceType = QUEEN;
                                break;

                            case 2:
                                piece.type = BISHOP;
                                promotionPieceType = BISHOP;
                                break;

                            case 3:
                                piece.type = KNIGHT;
                                promotionPieceType = KNIGHT;
                                break;

                        }

                        piece.texture = textures[i];
                        chosen = true;
                        break;
                    }

                }

            }

        }

    }

}