#ifndef GAME_H
#define GAME_H

#include "player.h"
using namespace std;
class Game
{
private:
    string modalita;
    bool gameIsOver;
    bool randomColor(); // funzione privata per assegnare un colore casuale al giocatore
public:
    Game(string modalita);               // costruttore
    void start();                        // funzione che contiene il ciclo del gioco
    bool sottoScacco(Player &, Board &); // true se il re del giocatore che invoca la funzione è sottoscacco
    bool scaccoMatto(Player &);          // true se il re del giocatore che invoca la funzione è in scaccomatto
};

#endif