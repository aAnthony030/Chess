#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <utility>
#include "Piecetypes.h"
#include "Rendering.h"

using PieceTypes::PAWN;
using PieceTypes::BISHOP;
using PieceTypes::KNIGHT;
using PieceTypes::ROOK;
using PieceTypes::QUEEN;
using PieceTypes::KING;

template <typename T>
// se si prova a chiudere il programma quando è in fase di selezione non viene permesso
void rendering_promote(T& piece, SDL_Renderer* renderer, SDL_Window* window) {
    const int cellsize = 80;

    SDL_Texture* textures[4] = {
        piece.isWhite ? IMG_LoadTexture(renderer, "C:\\Projects\\Game\\pieces\\white-rook.png") : IMG_LoadTexture(renderer, "C:\\Projects\\Game\\pieces\\black-rook.png"),
        piece.isWhite ? IMG_LoadTexture(renderer, "C:\\Projects\\Game\\pieces\\white-queen.png") : IMG_LoadTexture(renderer, "C:\\Projects\\Game\\pieces\\black-queen.png"),
        piece.isWhite ? IMG_LoadTexture(renderer, "C:\\Projects\\Game\\pieces\\white-bishop.png") : IMG_LoadTexture(renderer, "C:\\Projects\\Game\\pieces\\black-bishop.png"),
        piece.isWhite ? IMG_LoadTexture(renderer, "C:\\Projects\\Game\\pieces\\white-knight.png") : IMG_LoadTexture(renderer, "C:\\Projects\\Game\\pieces\\black-knight.png")
    };

    // se la finestra non è più grande essa non permette una scelta adeguata dei pezzi
    SDL_SetWindowSize(window, 640, 640);

    SDL_SetRenderDrawColor(renderer, 240, 217, 181, 255); // casella chiaro
    SDL_RenderClear(renderer);

    for (int i = 0; i < 4; i++) {
        SDL_FRect cordinate = {float(i*cellsize), float(0), float(cellsize), float(cellsize) };
        SDL_RenderTexture(renderer, textures[i], nullptr, &cordinate);
    }
    
    SDL_RenderPresent(renderer);

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
                                break;

                            case 1:
                                piece.type = QUEEN;
                                break;

                            case 2:
                                piece.type = BISHOP;
                                break;

                            case 3:
                                piece.type = KNIGHT;
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
        SDL_SetWindowSize(window, 640, 640);

    }

