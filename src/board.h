#ifndef BOARD_H
#define BOARD_H

#include "pezzo.h"
#include <array>
using namespace std;

class Pezzo; //forward declaration per evitare circular dependencies 
class Board
{
private:
    array<array<Pezzo *, 8>, 8> board;

public:
    Board();
    ~Board();  //distruttore 
    void printScacchiera();
    void spostaPezzo(int rigaI, int colonnaI, int rigaF, int colonnaF);
    void setPezzo(Pezzo *P, int riga, int colonna);
    Pezzo *getPezzo(int riga, int colonna) const;
};

#endif