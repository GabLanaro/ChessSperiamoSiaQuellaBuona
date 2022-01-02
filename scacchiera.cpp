#include <iostream>
#include <string>
#include "game.h"
using namespace std;
int main(int argc, char* argv[]){
    string modalita{argv[1]};
    //controllo che l'argomento inserito da linea di comando sia valido
    if(modalita!="cc" && modalita!="pc"){
        cout<<"La modalità di gioco inserita non è valida,\nSi riesegua il programma usando come argomento \"pc\" o \"cc\"\n";
        return 0;
    }
    cout<<"*******************************************\n";
    cout<<"Benvenuto al gioco degli scacchi\n";
    cout<<"La modalità di gioco scelta è: "<<argv[1]<<endl;
    Game gioco(modalita);    //creazione del gioco
    gioco.start();
    return 0;
}
