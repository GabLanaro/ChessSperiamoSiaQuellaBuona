#ifndef PEZZO_H
#define PEZZO_H
#include "board.h"
#include "iostream"

class Board; //forward declaration per evitare circular dependencies
class Pezzo{
    protected:
    char name;  //nome del Pezzo
    bool color;  //colore del pezzo("true"=white, "false"=black)
    int rigaPed;
    int colonnaPed;

    public:
    virtual ~Pezzo();  //distruttore 
    char getName() const;  //nome del Pezzo
    bool getColor() const;  //colore del Pezzo
    int getRigaPed();
    int getColonnaPed(); 
    virtual bool isValid(int rIni, int cIni, int rFin, int cFin, Board& b) = 0;  //check di validità delle mosse(funzione virtuale pura)

};

class Pedone : public Pezzo{
    public:
    virtual ~Pedone();  //distruttore
    Pedone(bool c, char n);
    bool isValid(int rIni, int cIni, int rFin, int cFin, Board& b);
};

class Torre : public Pezzo{
   /* private:
    Pezzo *p;*/

    public:
    virtual ~Torre();  //distruttore
    Torre(bool c, char n);
    bool isValid(int rIni, int cIni, int rFin, int cFin, Board& b);
};

class Alfiere : public Pezzo{
    public:
    virtual ~Alfiere();  //distruttore
    Alfiere(bool c, char n);
    bool isValid(int rIni, int cIni, int rFin, int cFin, Board& b);
};

class Cavallo : public Pezzo{
    public:
    virtual ~Cavallo();  //distruttore
    Cavallo(bool c, char n);
    bool isValid(int rIni, int cIni, int rFin, int cFin, Board& b);
};

class Regina : public Pezzo{
    public:
    virtual ~Regina();  //distruttore
    Regina(bool c, char n);
    bool isValid(int rIni, int cIni, int rFin, int cFin, Board& b);
};

class Re : public Pezzo{
    public:
    virtual ~Re();  //distruttore
    Re(bool c, char n);
    bool isValid(int rIni, int cIni, int rFin, int cFin, Board& b);
};

#endif