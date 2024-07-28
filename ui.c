#include <SDL.h>
#include <stdio.h>

// TODO: Math to draw an X or Square

void drawCircle(SDL_Renderer* renderer, int centreX, int centreY, int radius)
{
    const int diameter = (radius * 2);

    int x = (radius - 1);
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);

  while (x >= y)
  {
    // Each of the following renders an octant of the circle
    SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
    SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
    SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
    SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
    SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
    SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
    SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
    SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

    if (error <= 0)
    {
    	++y;
    	error += ty;
    	ty += 2;
    }

    if (error > 0)
    {
    	--x;
    	tx += 2;
    	error += (tx - diameter);
    }
  }
}


int returnLoc(int x, int y) {
  int loc = 0;

  if (y > 160 && y < 320)
      loc = 3;
  else if (y > 320)
      loc = 6;

  if (x > 210 && x < 420)
    loc += 1;
  else if (x > 420)
    loc += 2;

  return loc;
}

void drawBoard(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(renderer);
  
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 245);

  // Draw Horizontal Lines
  SDL_RenderDrawLine(renderer, 0, 160, 640, 160);
  SDL_RenderDrawLine(renderer, 0, 320, 640, 320);

  // Draw Vertical Lines
  SDL_RenderDrawLine(renderer, 210, 0, 210, 480);
  SDL_RenderDrawLine(renderer, 420, 0, 420, 480);
}

void drawX(SDL_Renderer *renderer, int x, int y) {
  int x1 = 5, x2 = 205, y1 = 5, y2 = 155;
  
  if (y > 0)
    x1 += (y * 210), x2 += (y * 210);

  if (x > 0)
    y1 += (x * 160), y2 += (x * 160);

  SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
  SDL_RenderDrawLine(renderer, x2, y1, x1, y2);
}

void drawO(SDL_Renderer *renderer, int x, int y) {
  int radius = 80;
  int centreX = 105, centreY = 80; 

  if (x > 0)
    centreX += (x * 210);
  if (y > 0)
    centreY += (y * 160);

  drawCircle(renderer, centreX, centreY, radius);
}
