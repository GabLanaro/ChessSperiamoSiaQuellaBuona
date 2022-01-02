#include "pezzo.h"
Pezzo::Pezzo(bool colore)
{
    this->colore = colore;
    stato = true; // pezzo inizializzato come vivo
}
void Pezzo::mossa()
{
}
char Pezzo::getNome()
{
    return 'c';
}
