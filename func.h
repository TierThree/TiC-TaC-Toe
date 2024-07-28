// UI functions
int returnLoc(int x, int y);
void drawBoard(SDL_Renderer *renderer);
void drawX(SDL_Renderer *renderer, int x, int y);
void drawO(SDL_Renderer *renderer, int x, int y);
void drawCircle(SDL_Renderer *renderer, int centreX, int centreY, int radius);

// Game functions
bool legalMove(int board[3][3], int x, int y);
bool checkLine(int line[3], int turn);
bool checkWin(int board[3][3], int turn);
Coordinates returnCoord(int loc);
