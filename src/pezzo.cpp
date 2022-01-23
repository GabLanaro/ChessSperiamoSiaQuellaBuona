//FILIPPO MORBIATO

#include "pezzo.h"
#include "board.h"
#include "iostream"

char Pezzo::getName() const // resituisce il nome del pezzo
{
    return name;
}

bool Pezzo::getColor() const // restituisce il colore del pezzo
{
    return color;
}

/*
int Pezzo::getColonnaPed()      //restituisce la colonna del pedone su cui viene effettuato l'en passant
{
    return colonnaPed;
}
*/

Pezzo::~Pezzo() {} // distruttore di pezzo

//*****PEDONE****

Pedone::~Pedone() {} // distruttore di pedone

Pedone::Pedone(bool c, char n) // costruttore di pedone
{
    color = c;
    name = n;
}

bool Pedone::isValid(int rIni, int cIni, int rFin, int cFin, Board &b)
{
    Pezzo *PezzoIniziale = b.getPezzo(rIni, cIni); // Creo un puntatore al pezzo iniziale
    Pezzo *PezzoFinale = b.getPezzo(rFin, cFin);   // Creo un puntatore al pezzo d'arrivo
    if (name == 'p')
    { // Se è bianco
        if ((rFin == rIni + 1) && (cFin == cIni) && (PezzoFinale == NULL))
        {                // Se la mossa che sta facendo è andare avanti di una cella e non c'è nessun pezzo
            return true; // Allora la mossa è valida
        }

        if ((rIni == 1) && (rFin == 3) && (cFin == cIni) && (PezzoFinale == NULL) && (b.getPezzo(rIni + 1, cFin) == NULL))
        { // Se la mossa che sta facendo è la prima , può andare avanti di due celle
            // e se nel tragitto e nella cella d'arrivo non ci sono pezzi
            /*colonnaPed = cFin;*/
            return true; // Allora la mossa è valida
        }

        if ((rFin == rIni + 1) && ((cFin == cIni + 1) || (cFin == cIni - 1)) && (PezzoFinale != NULL) && (PezzoFinale->getColor() != PezzoIniziale->getColor()))
        {                // Se nella cella in cui si sposta (muove in obliquo) c'è un pezzo
                         // e ha un colore diverso dal colore del giocatore
            return true; // Allora la mossa è valida
        }
    }
    else if (name == 'P')
    { // Se è nero
        if ((rFin == rIni - 1) && (cFin == cIni) && (PezzoFinale == NULL))
        {                // Se la mossa che sta facendo è andare avanti di una cella e non c'è nessun pezzo
            return true; // Allora la mossa è valida
        }

        if ((rIni == 6) && (rFin == 4) && (cFin == cIni) && (PezzoFinale == NULL) && (b.getPezzo(rIni - 1, cFin) == NULL))
        { // Se la mossa che sta facendo è la prima , può andare avanti di due celle e se nel tragitto e nella cella d'arrivo non ci sono pezzi
            /*colonnaPed = cFin;*/
            return true; // Allora la mossa è valida
        }

        if ((rFin == rIni - 1) && ((cFin == cIni - 1) || (cFin == cIni + 1)) && (PezzoFinale != NULL) && (PezzoFinale->getColor() != PezzoIniziale->getColor()))
        {                // Se nella cella in cui si sposta (muove in obliquo) c'è un pezzo e ha un colore diverso dal colore del giocatore
            return true; // Allora la mossa è valida
        }
    }

    return false;
}

//*****TORRE*****

Torre::~Torre() {} // distruttore di Torre

Torre::Torre(bool c, char n) // costruttore di Torre
{
    color = c;
    name = n;
}

bool Torre::isValid(int rIni, int cIni, int rFin, int cFin, Board &b)
{
    Pezzo *PezzoIniziale = b.getPezzo(rIni, cIni); // Creo un puntatore al pezzo iniziale
    if (cIni == cFin)
    { // Se si sta spostando in verticale
        if (rIni > rFin)
        { // Se si sta spostando in basso
            for (int i = rIni - 1; i >= rFin; i--)
            {                                               // Controllo ogni cella verso il basso
                Pezzo *PezzoCorrente = b.getPezzo(i, cFin); // Creo un puntatore che segue il pezzo verso il basso
                if (i == rFin)
                { // Se l'indice arriva alla cella finale
                    if (((PezzoCorrente != NULL) && (PezzoCorrente->getColor() != PezzoIniziale->getColor())) || (PezzoCorrente == NULL))
                    {                // Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; // Allora la mossa è valida
                    }
                }

                if (PezzoCorrente != NULL)
                {                 // Se le celle che incontra presentano un pezzo
                    return false; // Allora la mossa non è valida
                }
            }
        }
        else if (rIni < rFin)
        { // Se si sta spostando verso l'alto
            for (int i = rIni + 1; i <= rFin; i++)
            {                                               // Controllo ogni cella verso l'alto
                Pezzo *PezzoCorrente = b.getPezzo(i, cFin); // Creo un puntatore che segue il pezzo verso l'alto
                if (i == rFin)
                { // Se l'indice arriva alla posizione finale
                    if (((PezzoCorrente != NULL) && (PezzoCorrente->getColor() != PezzoIniziale->getColor())) || (PezzoCorrente == NULL))
                    {                // Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; // Allora la mossa è valida
                    }
                }

                if (PezzoCorrente != NULL)
                {                 // Se le celle che incontra presentano un pezzo
                    return false; // Allora la mossa non è valida
                }
            }
        }
    }
    else if (rIni == rFin)
    { // Se si sta spostando in orizzontale
        if (cIni > cFin)
        { // Se si sta spostando verso sinistra
            for (int i = cIni - 1; i >= cFin; i--)
            {                                               // Controllo ogni cella verso sinistra
                Pezzo *PezzoCorrente = b.getPezzo(rFin, i); // Creo un puntatore che segue il pezzo verso sinistra
                if (i == cFin)
                { // Se l'indice arriva alla posizione finale
                    if (((PezzoCorrente != NULL) && (PezzoCorrente->getColor() != PezzoIniziale->getColor())) || (PezzoCorrente == NULL))
                    {                // Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; // Allora la mossa è valida
                    }
                }

                if (PezzoCorrente != NULL)
                {                 // Se le celle che incontra presentano un pezzo
                    return false; // Allora la mossa non è valida
                }
            }
        }
        else if (cIni < cFin)
        { // Se si sta spostando verso destra
            for (int i = cIni + 1; i <= cFin; i++)
            {                                               // Controllo ogni cella verso destra
                Pezzo *PezzoCorrente = b.getPezzo(rFin, i); // Creo un puntatore che segue il pezzo verso destra
                if (i == cFin)
                { // Se l'indice arriva alla posizione finale
                    if (((PezzoCorrente != NULL) && (PezzoCorrente->getColor() != PezzoIniziale->getColor())) || (PezzoCorrente == NULL))
                    {                // Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; // Allora la mossa è valida
                    }
                }

                if (PezzoCorrente != NULL)
                {                 // Se le celle che incontra presentano un pezzo
                    return false; // Allora la mossa non è valida
                }
            }
        }
    }

    return false;
}

//*****CAVALLO*****

Cavallo::~Cavallo() {} // distruttore di Cavallo

Cavallo::Cavallo(bool c, char n) // costruttore di Cavallo
{
    color = c;
    name = n;
}

bool Cavallo::isValid(int rIni, int cIni, int rFin, int cFin, Board &b)
{
    Pezzo *PezzoIniziale = b.getPezzo(rIni, cIni); // Creo un puntatore al pezzo iniziale
    Pezzo *PezzoFinale = b.getPezzo(rFin, cFin);   // Creo un puntatore alla cella d'arrivo
    if (((cFin == cIni + 1) || (cFin == cIni - 1)) && ((rFin == rIni + 2) || (rFin == rIni - 2)))
    { // Se si sposta di una colonna a destra o sinistra e di due righe in alto o in basso
        if (((PezzoFinale != NULL) && (PezzoFinale->getColor() != PezzoIniziale->getColor())) || (PezzoFinale == NULL))
        {                // Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
            return true; // Allora la mossa è valida
        }
    }
    else if (((cFin == cIni + 2) || (cFin == cIni - 2)) && ((rFin == rIni + 1) || (rFin == rIni - 1)))
    { // Se si sposta di due colonne a destra o sinistra e di una riga in alto o in basso
        if (((PezzoFinale != NULL) && (PezzoFinale->getColor() != PezzoIniziale->getColor())) || (PezzoFinale == NULL))
        {                // Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
            return true; // Allora la mossa è valida
        }
    }
    return false;
}

//*****ALFIERE*****

Alfiere::~Alfiere() {} // distruttore di Alfiere

Alfiere::Alfiere(bool c, char n) // costruttore di Alfiere
{
    color = c;
    name = n;
}

bool Alfiere::isValid(int rIni, int cIni, int rFin, int cFin, Board &b)
{
    Pezzo *PezzoIniziale = b.getPezzo(rIni, cIni); // Creo un puntatore al pezzo iniziale
    int i, j;                                      // indici i->riga, j->colonna
    if (cIni < cFin)
    { // Se ci si sta spostando verso destra
        if (rIni < rFin)
        { // Dal basso verso l'alto
            for (i = rIni + 1, j = cIni + 1; ((i <= rFin) && (j <= cFin)); i++, j++)
            {                                            // Per ogni cella che si attraversa
                Pezzo *PezzoCorrente = b.getPezzo(i, j); // Creo un puntatore che segue il pezzo verso l'alto in diagonale
                if ((i == rFin) && (j == cFin))
                { // Se l'indice arriva alla posizione finale
                    if (((PezzoCorrente != NULL) && (PezzoCorrente->getColor() != PezzoIniziale->getColor())) || (PezzoCorrente == NULL))
                    {                // Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; // Allora la mossa è valida
                    }
                }

                if (PezzoCorrente != NULL)
                {                 // Se le celle che incontra presentano un pezzo
                    return false; // Allora la mossa non è valida
                }
            }
        }
        else if (rIni > rFin)
        { // Dall'alto verso il basso
            for (i = rIni - 1, j = cIni + 1; ((i >= rFin) && (j <= cFin)); i--, j++)
            {                                            // Per ogni cella che si attraversa
                Pezzo *PezzoCorrente = b.getPezzo(i, j); // Creo un puntatore che segue il pezzo verso il basso in diagonale
                if ((i == rFin) && (j == cFin))
                { // Se l'indice arriva alla posizione finale
                    if (((PezzoCorrente != NULL) && (PezzoCorrente->getColor() != PezzoIniziale->getColor())) || (PezzoCorrente == NULL))
                    {                // Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; // Allora la mossa è valida
                    }
                }

                if (PezzoCorrente != NULL)
                {                 // Se le celle che incontra presentano un pezzo
                    return false; // Allora la mossa non è valida
                }
            }
        }
    }
    else if (cIni > cFin)
    { // Se si sta spostando verso sinistra
        if (rIni < rFin)
        { // Dal basso verso l'alto
            for (i = rIni + 1, j = cIni - 1; ((i <= rFin) && (j >= cFin)); i++, j--)
            {                                            // Per ogni cella che si attraversa
                Pezzo *PezzoCorrente = b.getPezzo(i, j); // Creo un puntatore che segue il pezzo verso l'alto in diagonale
                if ((i == rFin) && (j == cFin))
                { // Se l'indice arriva alla posizione finale
                    if (((PezzoCorrente != NULL) && (PezzoCorrente->getColor() != PezzoIniziale->getColor())) || (PezzoCorrente == NULL))
                    {                // Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; // Allora la mossa è valida
                    }
                }

                if (PezzoCorrente != NULL)
                {                 // Se le celle che incontra presentano un pezzo
                    return false; // Allora la mossa non è valida
                }
            }
        }
        else if (rIni > rFin)
        { // Dall'alto verso il basso
            for (i = rIni - 1, j = cIni - 1; ((i >= rFin) && (j >= cFin)); i--, j--)
            {                                            // Per ogni cella che si attraversa
                Pezzo *PezzoCorrente = b.getPezzo(i, j); // Creo un puntatore che segue il pezzo verso il basso in diagonale
                if ((i == rFin) && (j == cFin))
                { // Se l'indice arriva alla posizione finale
                    if (((PezzoCorrente != NULL) && (PezzoCorrente->getColor() != PezzoIniziale->getColor())) || (PezzoCorrente == NULL))
                    {                // Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; // Allora la mossa è valida
                    }
                }

                if (PezzoCorrente != NULL)
                {                 // Se le celle che incontra presentano un pezzo
                    return false; // Allora la mossa non è valida
                }
            }
        }
    }

    return false;
}

//*****REGINA*****

Regina::~Regina() {} // distruttore di Regina

Regina::Regina(bool c, char n) // costruttore di Regina
{
    color = c;
    name = n;
}

bool Regina::isValid(int rIni, int cIni, int rFin, int cFin, Board &b)
{
    // Data dai movimenti di Alfiere + Torre
    Pezzo *PezzoIniziale = b.getPezzo(rIni, cIni); // Creo un puntatore al pezzo iniziale
    // Controlli in obliquo (Alfiere)
    int i, j; // indici i->riga, j->colonna
    if (cIni < cFin)
    { // Se ci si sta spostando verso destra
        if (rIni < rFin)
        { // Dal basso verso l'alto
            for (i = rIni + 1, j = cIni + 1; ((i <= rFin) && (j <= cFin)); i++, j++)
            {                                            // Per ogni cella che si attraversa
                Pezzo *PezzoCorrente = b.getPezzo(i, j); // Creo un puntatore che segue il pezzo verso l'alto in diagonale
                if ((i == rFin) && (j == cFin))
                { // Se l'indice arriva alla posizione finale
                    if (((PezzoCorrente != NULL) && (PezzoCorrente->getColor() != PezzoIniziale->getColor())) || (PezzoCorrente == NULL))
                    {                // Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; // Allora la mossa è valida
                    }
                }

                if (PezzoCorrente != NULL)
                {                 // Se le celle che incontra presentano un pezzo
                    return false; // Allora la mossa non è valida
                }
            }
        }
        else if (rIni > rFin)
        { // Dall'alto verso il basso
            for (i = rIni - 1, j = cIni + 1; ((i >= rFin) && (j <= cFin)); i--, j++)
            {                                            // Per ogni cella che si attraversa
                Pezzo *PezzoCorrente = b.getPezzo(i, j); // Creo un puntatore che segue il pezzo verso il basso in diagonale
                if ((i == rFin) && (j == cFin))
                { // Se l'indice arriva alla posizione finale
                    if (((PezzoCorrente != NULL) && (PezzoCorrente->getColor() != PezzoIniziale->getColor())) || (PezzoCorrente == NULL))
                    {                // Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; // Allora la mossa è valida
                    }
                }

                if (PezzoCorrente != NULL)
                {                 // Se le celle che incontra presentano un pezzo
                    return false; // Allora la mossa non è valida
                }
            }
        }
    }
    else if (cIni > cFin)
    { // Se si sta spostando verso sinistra
        if (rIni < rFin)
        { // Dal basso verso l'alto
            for (i = rIni + 1, j = cIni - 1; ((i <= rFin) && (j >= cFin)); i++, j--)
            {                                            // Per ogni cella che si attraversa
                Pezzo *PezzoCorrente = b.getPezzo(i, j); // Creo un puntatore che segue il pezzo verso l'alto in diagonale
                if ((i == rFin) && (j == cFin))
                { // Se l'indice arriva alla posizione finale
                    if (((PezzoCorrente != NULL) && (PezzoCorrente->getColor() != PezzoIniziale->getColor())) || (PezzoCorrente == NULL))
                    {                // Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; // Allora la mossa è valida
                    }
                }

                if (PezzoCorrente != NULL)
                {                 // Se le celle che incontra presentano un pezzo
                    return false; // Allora la mossa non è valida
                }
            }
        }
        else if (rIni > rFin)
        { // Dall'alto verso il basso
            for (i = rIni - 1, j = cIni - 1; ((i >= rFin) && (j >= cFin)); i--, j--)
            {                                            // Per ogni cella che si attraversa
                Pezzo *PezzoCorrente = b.getPezzo(i, j); // Creo un puntatore che segue il pezzo verso il basso in diagonale
                if ((i == rFin) && (j == cFin))
                { // Se l'indice arriva alla posizione finale
                    if (((PezzoCorrente != NULL) && (PezzoCorrente->getColor() != PezzoIniziale->getColor())) || (PezzoCorrente == NULL))
                    {                // Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; // Allora la mossa è valida
                    }
                }

                if (PezzoCorrente != NULL)
                {                 // Se le celle che incontra presentano un pezzo
                    return false; // Allora la mossa non è valida
                }
            }
        }
    }

    // Controlli in verticale e orizzontale (Torre)
    if (cIni == cFin)
    { // Se si sta spostando in verticale
        if (rIni > rFin)
        { // Se si sta spostando in basso
            for (int i = rIni - 1; i >= rFin; i--)
            {                                               // Controllo ogni cella verso il basso
                Pezzo *PezzoCorrente = b.getPezzo(i, cFin); // Creo un puntatore che segue il pezzo verso il basso
                if (i == rFin)
                { // Se l'indice arriva alla cella finale
                    if (((PezzoCorrente != NULL) && (PezzoCorrente->getColor() != PezzoIniziale->getColor())) || (PezzoCorrente == NULL))
                    {                // Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; // Allora la mossa è valida
                    }
                }

                if (PezzoCorrente != NULL)
                {                 // Se le celle che incontra presentano un pezzo
                    return false; // Allora la mossa non è valida
                }
            }
        }
        else if (rIni < rFin)
        { // Se si sta spostando verso l'alto
            for (int i = rIni + 1; i <= rFin; i++)
            {                                               // Controllo ogni cella verso l'alto
                Pezzo *PezzoCorrente = b.getPezzo(i, cFin); // Creo un puntatore che segue il pezzo verso l'alto
                if (i == rFin)
                { // Se l'indice arriva alla posizione finale
                    if (((PezzoCorrente != NULL) && (PezzoCorrente->getColor() != PezzoIniziale->getColor())) || (PezzoCorrente == NULL))
                    {                // Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; // Allora la mossa è valida
                    }
                }

                if (PezzoCorrente != NULL)
                {                 // Se le celle che incontra presentano un pezzo
                    return false; // Allora la mossa non è valida
                }
            }
        }
    }
    else if (rIni == rFin)
    { // Se si sta spostando in orizzontale
        if (cIni > cFin)
        { // Se si sta spostando verso sinistra
            for (int i = cIni - 1; i >= cFin; i--)
            {                                               // Controllo ogni cella verso sinistra
                Pezzo *PezzoCorrente = b.getPezzo(rFin, i); // Creo un puntatore che segue il pezzo verso sinistra
                if (i == cFin)
                { // Se l'indice arriva alla posizione finale
                    if (((PezzoCorrente != NULL) && (PezzoCorrente->getColor() != PezzoIniziale->getColor())) || (PezzoCorrente == NULL))
                    {                // Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; // Allora la mossa è valida
                    }
                }

                if (PezzoCorrente != NULL)
                {                 // Se le celle che incontra presentano un pezzo
                    return false; // Allora la mossa non è valida
                }
            }
        }
        else if (cIni < cFin)
        { // Se si sta spostando verso destra
            for (int i = cIni + 1; i <= cFin; i++)
            {                                               // Controllo ogni cella verso destra
                Pezzo *PezzoCorrente = b.getPezzo(rFin, i); // Creo un puntatore che segue il pezzo verso destra
                if (i == cFin)
                { // Se l'indice arriva alla posizione finale
                    if (((PezzoCorrente != NULL) && (PezzoCorrente->getColor() != PezzoIniziale->getColor())) || (PezzoCorrente == NULL))
                    {                // Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; // Allora la mossa è valida
                    }
                }

                if (PezzoCorrente != NULL)
                {                 // Se le celle che incontra presentano un pezzo
                    return false; // Allora la mossa non è valida
                }
            }
        }
    }

    return false;
}

//*****RE*****

Re::~Re() {} // distruttore di Re

Re::Re(bool c, char n) // costruttore di Re
{
    color = c;
    name = n;
}

bool Re::isValid(int rIni, int cIni, int rFin, int cFin, Board &b)
{
    Pezzo *PezzoIniziale = b.getPezzo(rIni, cIni); // Creo un puntatore al pezzo iniziale
    Pezzo *PezzoFinale = b.getPezzo(rFin, cFin);   // Creo un puntatore alla cella d'arrivo
    if (((rFin == rIni + 1) || (rFin == rIni - 1) || (rFin == rIni)) && ((cFin == cIni + 1) || (cFin == cIni - 1) || (cFin == cIni)))
    { // Se si sta spostando di una cella in qualsiasi direzione
        if (((PezzoFinale != NULL) && (PezzoFinale->getColor() != PezzoIniziale->getColor())) || (PezzoFinale == NULL))
        {                // Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
            return true; // Allora la mossa è valida
        }
    }

    return false;
}