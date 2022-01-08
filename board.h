#ifndef BOARD_H
#define BOARD_H

#include "pezzo.h"
#include <array>
using namespace std;

class Board
{
private:
    array<array<Pezzo *, 8>, 8> board;

public:
    Board();
    void printScacchiera();
    void spostaPezzo(int rigaI, int colonnaI, int rigaF, int colonnaF);
    bool isMoveValid(int rigaI, int colonnaI, int rigaF, int colonnaF);
    void setPezzo(Pezzo *P, int riga, int colonna);
    Pezzo *getPezzo(int riga, int colonna);
};

#endif