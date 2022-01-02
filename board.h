#include "pezzo.h"

class Board
{
private:
    Pezzo* board[8][8];

public:
    Board();
    void printScacchiera();
    void spostaPezzo();
    bool isMoveValid(int rigaI,int colonnaI,int rigaF,int colonnaF);
};