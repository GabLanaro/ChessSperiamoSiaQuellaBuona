#include <string>
#include <iostream>
#include <tuple>
#include <cctype>
#include <ctime>
#include "player.h"
#include "board.h"


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

bool Player::getTipo() const
{
    return tipo;
}

void Player::setTipo(bool tipo)
{
    this->tipo = tipo;
}

tuple<int, int, int, int> Player::mossa(Board &board)
{
    if (this->tipo == true)
    {
        // true=umano
        cout << "inserisci mossa: ";
        string input;

        // CONTROLLI INPUT LESSICO E RANGE
        bool inputValido = false;
        while (!inputValido)
        {
            getline(cin, input);
            if (input == "XX XX" || input == "xx xx")
            {
                // stampa la scacchiera
                board.printScacchiera();
                cout<<"\ninserisci mossa: ";
            }
            else if (toupper(input[0]) >= 'A' && toupper(input[0]) <= 'H' &&
                     toupper(input[3]) >= 'A' && toupper(input[3]) <= 'H' &&
                     input[1] >= '1' && input[1] <= '8' &&
                     input[4] >= '1' && input[4] <= '8' &&
                     input[2] == ' ' && input[0] + input[1] != input[3] + input[4]) // check validità lettere/numeri
            {
                inputValido = true;
            }
            else
            {
                cout << "L'input che hai inserito non \212 valido,\ninserisci mossa: ";
            }
        }

        int colIniz = (int)toupper(input[0]) - 65; // Il codice ASCII di 'A' è 65
        int rigIniz = input[1] - 49;               // domani vi faccio un audio e vi spiego perchè 49
        int colFin = (int)toupper(input[3]) - 65;
        int rigFin = input[4] - 49;
        return make_tuple(colIniz, rigIniz, colFin, rigFin);
    }
    else
    {                                   
        int colIniz, rigIniz, colFin, rigFin;
        rigIniz = rand() % 8; //numero intero random tra 0 e 8
        colIniz =rand() % 8;
        rigFin=rand() % 8;
        colFin=rand() % 8;
        
        cout<<rigIniz<<colIniz<<" "<<colFin<<rigFin<<" ";
        return make_tuple(colIniz, rigIniz, colFin, rigFin);
    }
}