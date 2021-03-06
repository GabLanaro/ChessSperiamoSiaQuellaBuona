//GABRIELE TURETTA

#ifndef PLAYER_H
#define PLAYER_H

#include <tuple>
#include "board.h"

class Player
{
private:
    bool colore; // true=white,false=black
    bool tipo;   // true=umano,false=computer

public:
    Player(bool colore, bool tipo);
    bool getColor() const;
    bool getTipo() const;
    void setTipo(bool tipo);
    std::tuple<int, int, int, int> mossa(Board &board);
    bool rispPatta();
};

#endif