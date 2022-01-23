#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "board.h"
#include <vector>
using namespace std;
class Game
{
private:
    string modalita;
    bool gameIsOver;
    bool randomColor(); // funzione privata per assegnare un colore casuale al giocatore
public:
    Game(string modalita);                                                                               // costruttore
    void start();                                                                                        // funzione che contiene il ciclo del gioco
    bool isMoveValid(int rigaI, int colonnaI, int rigaF, int colonnaF, Player *currentPlayer, Board &b); // check di validità generali mossa
    bool sottoScacco(Player &, Board &);                                                                 // true se il re del giocatore che invoca la funzione è sottoscacco
    bool scaccoMatto(Player &, Board &);                                                                 // true se il re del giocatore che invoca la funzione è in scaccomatto
    bool promozione(Board &, int rigaF, int colonnaF,bool);                                                   // gestione della mossa speciale Promozione
    bool enPassant(Board &, int rigaI, int colonnaI, int rigaF, int colonnaF);                           // gestione della mossa speciale En Passant
    bool arrocco(Board &, vector<string>, bool, int);                                                    // gestione della mossa speciale Arrocco
    string creaStrBoard(Board &);                                                                        // crea delle stringhe raffiguranti la board
    int contaVuoti_P(string);                                                                            // crea degli int uguali alla somma del numero delle caselle vuote + la somma degli indici dei pedoni
    bool isPatta(vector<string>, vector<int>, string, int);                                              // gestisce la patta
};

#endif