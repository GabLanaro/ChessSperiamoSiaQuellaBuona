#ifndef PEZZO_H
#define PEZZO_H
#include "board.h"

class Board; //forward declaration per evitare circular dependencies
class Pezzo{
    protected:
    char name;  //nome del Pezzo
    bool color;  //colore del pezzo("true"=white, "false"=black)

    public:
    virtual ~Pezzo();  //distruttore 
    char getName() const;  //nome del Pezzo
    bool getColor() const;  //colore del Pezzo
    //int getPosition();  //posizione del pezzo
    //void setPosition();  //sposta il pezzo 
    virtual bool isValid(int rIni, int cIni, int rFin, int cFin, Board& b) = 0;  //check di validità delle mosse(funzione virtuale pura)

};

class Pedone : public Pezzo{
    public:
    Pedone(bool c, char n);
    bool isValid(int rIni, int cIni, int rFin, int cFin, Board& b);
};

class Torre : public Pezzo{
    public:
    Torre(bool c, char n);
    bool isValid(int rIni, int cIni, int rFin, int cFin, Board& b);
};

class Alfiere : public Pezzo{
    public:
    Alfiere(bool c, char n);
    bool isValid(int rIni, int cIni, int rFin, int cFin, Board& b);
};

class Cavallo : public Pezzo{
    public:
    Cavallo(bool c, char n);
    bool isValid(int rIni, int cIni, int rFin, int cFin, Board& b);
};

class Regina : public Pezzo{
    public:
    Regina(bool c, char n);
    bool isValid(int rIni, int cIni, int rFin, int cFin, Board& b);
};

class Re : public Pezzo{
    public:
    Re(bool c, char n);
    bool isValid(int rIni, int cIni, int rFin, int cFin, Board& b);
};

#endif