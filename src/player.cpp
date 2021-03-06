//GABRIELE TURETTA

#include <string>
#include <iostream>
#include <tuple>
#include <cctype>
#include <ctime>
#include <algorithm>
#include "player.h"
#include "board.h"

using namespace std;

Player::Player(bool colore, bool tipo) // costruttore
{
    this->colore = colore;
    this->tipo = tipo;
}

bool Player::getColor() const // restituisce il colore
{
    return colore;
}

bool Player::getTipo() const // restituisce il tipo
{
    return tipo;
}

void Player::setTipo(bool tipo) // imposta il tipo
{
    this->tipo = tipo;
}

tuple<int, int, int, int> Player::mossa(Board &board) // riceve e legge l'input dell'utente e del computer e ne restituisce le coordinate
{
    if (this->tipo == true) // true=umano
    {
        cout << "Inserisci mossa: ";
        string input;

        // CONTROLLI INPUT LESSICO E RANGE
        bool inputValido = false;
        while (!inputValido)
        {
            getline(cin, input);
            // PATTA
            if (input == "PATTA" || input == "patta")
            {
                cout << "Hai richiesto la patta\n";
                bool risposta = rispPatta();
                if (risposta)
                {
                    return make_tuple(-1, -1, -1, -1); // se la patta è stata accettata restituisce una tupla speciale
                }
                else
                {
                    cout << "Il Computer ha rifiutato la patta\nInserisci mossa: ";
                }
            }
            // ARROCCO
            else if (input == "ARROCCO DX" || input == "arrocco dx")
            {
                return make_tuple(-2, -2, -2, -2); //-2 valore speciale per la chiamata alla funzione arrocco in Game
            }
            else if (input == "ARROCCO SX" || input == "arrocco sx")
            {
                return make_tuple(-3, -3, -3, -3); //-3 valore speciale per la chiamata alla funzione arrocco in Game
            }

            if (input.size() != 5)
            {
                cout << "L'input che hai inserito non ha il numero corretto di caratteri.\nInserisci mossa: ";
            }
            else
            {
                string iniziale = input.substr(0, 2);
                string finale = input.substr(3, 2);
                // trasformazione in maiuscolo per favorire il controllo lessicale
                transform(iniziale.begin(), iniziale.end(), iniziale.begin(), ::toupper);
                transform(finale.begin(), finale.end(), finale.begin(), ::toupper);

                // STAMPA BOARD
                if (input == "XX XX" || input == "xx xx")
                {
                    // stampa la scacchiera
                    board.printScacchiera();
                    cout << "\nInserisci mossa: ";
                }
                // INSERIMENTO MOSSA
                else if (toupper(input[0]) >= 65 && toupper(input[0]) <= 72 && // I numeri 65 e 72 corrispondono ai
                         toupper(input[3]) >= 65 && toupper(input[3]) <= 72 && // codici ASCII delle lettere A e H
                         input[1] >= 49 && input[1] <= 56 &&                   // I numeri 49, 56 e 32 corrispondono ai
                         input[4] >= 49 && input[4] <= 56 &&                   // codici ASCII dei numeri 1, 8 e allo spazio
                         input[2] == 32 && iniziale != finale)
                {
                    inputValido = true;
                }
                else
                {
                    cout << "L'input che hai inserito non \212 valido,\nInserisci mossa: ";
                }
            }
        }
        int colIniz = (int)toupper(input[0]) - 65; // Il codice ASCII di 'A' è 65
        int rigIniz = input[1] - 49;
        int colFin = (int)toupper(input[3]) - 65;
        int rigFin = input[4] - 49;
        return make_tuple(colIniz, rigIniz, colFin, rigFin);
    }
    else // false=computer
    {
        int colIniz, rigIniz, colFin, rigFin;
        rigIniz = rand() % 8; // numero intero random tra 0 e 8
        colIniz = rand() % 8;
        rigFin = rand() % 8;
        colFin = rand() % 8;

        return make_tuple(colIniz, rigIniz, colFin, rigFin);
    }
}

// Metodo che risponde alla patta richiesta dall'utente col 10% di possibilità di accettare
bool Player::rispPatta()
{
    srand(time(NULL));
    bool x = rand() % 10; // numero intero random tra 0 e 10
    return !x;
}