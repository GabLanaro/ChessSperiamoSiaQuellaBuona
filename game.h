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
    void promozione(Board &, int rigaF, int colonnaF);
    bool enPassant(Board &, int rigaI, int colonnaI, int rigaF, int colonnaF);
    string isPatta(vector<string>, string, Board &);
};

#endif