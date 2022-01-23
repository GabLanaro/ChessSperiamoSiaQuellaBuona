#include <iostream>
#include <string>
#include "game.h"
using namespace std;

int main(int argc, char *argv[])
{
    string modalita{argv[1]};
    // controllo che l'argomento inserito da linea di comando sia valido
    if (modalita != "cc" && modalita != "pc")
    {
        cout << "La modalita' di gioco inserita non \212 valida,\nSi riesegua il programma usando come argomento \"pc\" o \"cc\"\n";
        return 0;
    }
    cout << "*****************************\n";
    cout << "Benvenuto al gioco degli scacchi\n";
    cout << "La modalita' di gioco scelta \212: " << argv[1] << endl;
    cout << "*****************************\n";
    cout << "comandi per giocare:\n-mossa: [rigaIniziale][colonnaIniziale] [rigaFInale][colonnaFInale]\n-stampa scacchiera: XX XX\n-patta: \"PATTA\"\n-arrocco: \"ARROCCO DX / ARROCCO SX\"";
    cout << "\n*****************************\n";
    Game gioco(modalita); // creazione del gioco
    gioco.start();
    return 0;
}
