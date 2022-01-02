#include <iostream>
#include <string>
#include <cctype>
#include <ctime>
#include "game.h"
#include "player.h"



Game::Game(string mod){
    modalita=mod;
}

void Game::start(){
    gameIsOver=false;   //verrà utilizzata nel ciclo do while per verificare che la partita non sia terminata
    //Board tavola();
    bool playerColor=randomColor(); //true=white, false=black
    Player player1(playerColor,false);
    if(tolower(modalita[0])=='p'){  //la modalità scelta è pc
        player1.setTipo(true);  //player1 è umano
    }
    Player player2(!playerColor,false);     //player2 è un computer ed è creato in entrambe le modalità.
    Player& currentPlayer=(player1.getColor()==true)? currentPlayer=player1 : currentPlayer=player2;    //currentPlayer è una reference al player bianco
    //CICLO CHE VERIFICA SCACCO E SCACCOMATTO, CHIEDE MOSSA, LA EFFETTUA E CAMBIA TURNO.
    do{
        if(sottoScacco(currentPlayer)){
            if(scaccoMatto(currentPlayer))  gameIsOver=true;
            else    cout<<"attenzione! Il tuo re è sottoscacco.";
        }
        //il re non è sottoscacco, currentPlayer inserisce mossa.
        currentPlayer.mossa();
    }while(!gameIsOver);
}  

bool Game::randomColor(){
    //true=white, false=black
    srand(time(NULL));  //seed
    bool x=rand()%2;    //numero intreo casuale tra 0 e 1
    return x & 1;       //funzione AND tra il numero casuale e 1
}

bool Game::sottoScacco(Player& p){
    return false;
}   


bool Game::scaccoMatto(Player& p){
    return false;
}


