#include "player.h"
#include <string>
#include <iostream>
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

void Player::mossa()
{
    if (this->tipo == true)
    {
        // true=umano
        cout << "inserisci mossa (Ex. C2 C3)";
        string input;
        cin >> input;
        //  CONTROLLI INPUT
        // Le lettere vanno convertite in Maiuscolo per favorire la conversione
        //lessico, range,

        // string posIniz = input.substr(0, 2);
        // string posFin = input.substr(3, 2);
        int colIniz = (int)input[0] - 65; // Il codice ASCII di 'A' è 65
        int rigIniz = input[1] - 1;
        int colFin = (int)input[3] - 65;
        int rigFin = input[4] - 1;

      
    }
}