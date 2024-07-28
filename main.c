#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include "struct.h"
#include "func.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

typedef enum Piece {
  noneE = 0,
  X = 1,
  O = 2
} Piece;

typedef struct State {
  int turn;
  int board[3][3];
} State;


// TODO: Math to draw an X or Square

int main() {
  // Initialize SDL required variables
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event event;
  bool quit = false;

  Piece nonePiece = noneE;
  Piece xPiece = X; 
  Piece oPiece = O;

  // Initialize the gamestate and set the default values
  State state = {
    .turn = xPiece,
    .board = {
      {nonePiece, nonePiece, nonePiece},
      {nonePiece, nonePiece, nonePiece},
      {nonePiece, nonePiece, nonePiece}
    }
  };

  State *gamestate = &state;

  if (SDL_Init(SDL_INIT_VIDEO)) {
    printf("Error: %s\n", SDL_GetError());
    return 1;
  }

  window = SDL_CreateWindow("TiC-TaC-Toe",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SCREEN_WIDTH,
                                    SCREEN_HEIGHT, 
                                    SDL_WINDOW_SHOWN);

  if (!window) {
    printf("Error: %s", SDL_GetError());
    return 1;
  }

  renderer = SDL_CreateRenderer(window,
                                        -1,
                                        SDL_RENDERER_ACCELERATED);

  if (!renderer) {
    printf("Error: %s", SDL_GetError());
    return 1;
  }

  drawBoard(renderer);
  SDL_RenderPresent(renderer);

  while (!quit) {
    SDL_Delay(1);
    SDL_PollEvent(&event);
    
    switch (event.type)
    {
      case SDL_QUIT:
        quit = true;
        break;
      case SDL_MOUSEBUTTONDOWN:
        SDL_MouseButtonEvent *click;
        click = &(event.button);

        int loc = returnLoc(
          click->x,
          click->y
        );

        Coordinates coord = returnCoord(loc);

        if (legalMove(gamestate->board, coord.x, coord.y)) {
          gamestate->board[coord.x][coord.y] = gamestate->turn;
          if (gamestate->turn == 1)
            drawX(renderer, coord.x, coord.y);
          else
            drawO(renderer, coord.y, coord.x);

          if (checkWin(gamestate->board, gamestate->turn)) {
            printf("Player %d has won!\n", gamestate->turn);
            quit = true;
          }
        }

        if (gamestate->turn == xPiece)
          gamestate->turn = oPiece;
        else
          gamestate->turn = xPiece;
        break;
      case SDL_MOUSEBUTTONUP:
        break;
    }

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
