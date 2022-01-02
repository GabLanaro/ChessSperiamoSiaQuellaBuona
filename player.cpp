#include <string>
#include <iostream>
#include <tuple>
#include "player.h"
using namespace std;

Player::Player(bool colore, bool tipo)
{
    this->colore = colore;
    this->tipo = tipo;
}


bool Player::getColor() const
{
    return colore;
}


void Player::setTipo(bool tipo)
{
    this->tipo = tipo;
}


tuple<int,int,int,int> Player::mossa()
{
    if (this->tipo == true)
    {
        // true=umano
        cout << "inserisci mossa (Ex. C2 C3): ";
        string input;
        cin >> input;
        //  CONTROLLI INPUT
        // Le lettere vanno convertite in Maiuscolo per favorire la conversione

        int colIniz = (int)input[0] - 65; // Il codice ASCII di 'A' è 65
        int rigIniz = input[1] - 1;
        int colFin = (int)input[3] - 65;
        int rigFin = input[4] - 1;
        return make_tuple(colIniz,rigIniz,colFin,rigFin);
    }
    else{//il giocatore è un computer, la mossa è casuale.
        return make_tuple(2,3,4,5); //gabriel ho fatto return a caso per continuare a lavorare su start
    }
}