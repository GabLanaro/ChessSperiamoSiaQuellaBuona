#include "pezzo.h"

class Board
{
private:
    Pezzo* board[8][8];

public:
    Board();
    void printScacchiera();
    void muovi();
};