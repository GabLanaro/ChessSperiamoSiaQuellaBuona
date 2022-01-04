#ifndef PEZZO_H
#define PEZZO_H

class Pezzo{
    protected:
    char name;  //nome del Pezzo
    bool color;  //colore del pezzo("true"=white, "false"=black)

    public:
    virtual ~Pezzo();  //distruttore 
    char getName() const;  //nome del Pezzo
    bool getColor() const;  //colore del Pezzo
    int getPosition();  //posizione del pezzo
    void setPosition();  //sposta il pezzo 
    virtual bool isValid(int ri, int rf, int ci, int cf) = 0;  //check di validità delle mosse(funzione virtuale pura)

};

class Pedone : public Pezzo{
    public:
    Pedone(bool color);
    bool isValid(/*...*/);
};

class Torre : public Pezzo{
    public:
    Torre(bool color);
    bool isValid(/*...*/);
};

class Alfiere : public Pezzo{
    public:
    Alfiere(bool color);
    bool isValid(/*...*/);
};

class Cavallo : public Pezzo{
    public:
    Cavallo(bool color);
    bool isValid(/*...*/);
};

class Re : public Pezzo{
    public:
    Re(bool color);
    bool isValid(/*...*/);
};

class Regina : public Pezzo{
    public:
    Regina(bool color);
    bool isValid(/*...*/);
};

#endif