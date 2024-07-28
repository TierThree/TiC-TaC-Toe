#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include "struct.h"

Coordinates returnCoord(int loc) {
  Coordinates point;

  if (loc == 0 || loc == 1 || loc == 2)
    point.x = 0, point.y = loc;
  else if (loc == 3 || loc == 4 || loc == 5)
    point.x = 1, point.y = (loc-3);
  else 
    point.x = 2, point.y = (loc-6);

  return point;
}

bool legalMove(int board[3][3], int x, int y) {
  if (board[x][y] == 0)
    return true;
  return false;
}

bool checkLine(int line[3], int turn) {
  for (int i = 0; i < 3; i++)
    if (line[i] != turn)
      return false;
  return true;
}

int flipInt(int i) {
  return ((i - 2) * -1); 
}

bool checkWin(int board[3][3], int turn) {
  int normalDiag[3];
  int backwardsDiag[3];

  for (int i = 0; i < 3; i++) {
    int line[3] = {
      board[0][i],
      board[1][i],
      board[2][i]
    };

    normalDiag[i] = board[i][i];
    backwardsDiag[i] = board[i][flipInt(i)];

    if (checkLine(board[i], turn) || checkLine(line, turn))
      return true;
  }

  if (checkLine(normalDiag, turn) || checkLine(backwardsDiag, turn))
    return true;
  
  return false;
}
