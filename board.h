#ifndef BOARD_H
#define BOARD_H

#include "pezzo.h"
#include <array>
using namespace std;

class Board
{
private:
    array<array<Pezzo*,8>,8> board;

public:
    Board();
    void printScacchiera();
    void spostaPezzo();
    bool isMoveValid(int rigaI,int colonnaI,int rigaF,int colonnaF);
};

#endif