//GABRIELE TURETTA

#ifndef BOARD_H
#define BOARD_H

#include "pezzo.h"
#include <array>
using namespace std;

class Pezzo; // forward declaration per evitare circular dependencies
class Board
{
private:
    array<array<Pezzo *, 8>, 8> board; // la scacchiera è un array di puntatori a pezzo
                                       // std::array è stato scelto per la sua dimensione fissa ed immutabile, come la scacchiera fisica
public:
    Board();
    ~Board();
    void printScacchiera();
    void spostaPezzo(int rigaI, int colonnaI, int rigaF, int colonnaF);
    void setPezzo(Pezzo *P, int riga, int colonna);
    Pezzo *getPezzo(int riga, int colonna) const;
};

#endif