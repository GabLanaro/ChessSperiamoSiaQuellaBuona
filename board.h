#ifndef BOARD_H
#define BOARD_H

#include "pezzo.h"
#include <array>
#include "player.h"
using namespace std;

class Player; //forward declaration per evitare circular dependencies
class Board
{
private:
    array<array<Pezzo *, 8>, 8> board;

public:
    Board();
    void printScacchiera();
    void spostaPezzo(int rigaI, int colonnaI, int rigaF, int colonnaF);
    bool isMoveValid(int rigaI, int colonnaI, int rigaF, int colonnaF, Player* currentPlayer);
    void setPezzo(Pezzo *P, int riga, int colonna);
    Pezzo *getPezzo(int riga, int colonna) const;
};

#endif