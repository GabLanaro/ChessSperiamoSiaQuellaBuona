#include <random>
#include <string>
#include <cctype>
#include "game.h"
#include "player.h"
#include <iostream>
Game::Game(string mod){
    modalita=mod;
}
void Game::start(){
    //Board tavola();
    bool playerColor=randomColor(); //true=white, false=blac
    Player player1(playerColor,true);
    if(tolower(modalita[0])=='p'){  //la modalità scelta è pc
        player1.setTipo(true);  //player1 è umano
    }
    else                    
        player1.setTipo(false); //modalità scelta è cc, il primo giocatore è un computer.
    Player player2(!playerColor,false);     //player2 è un computer ed è creato in entrambe le modalità.
    Player& currentPlayer=(player1.getColor()==true)? currentPlayer=player1 : currentPlayer=player2;
}  


bool Game::sottoscacco(){
    return false;
}   


bool Game::scaccomatto(){
    return false;
}


bool Game::randomColor(){
    //true=white, false=black
    //nota: non è stato utilizzato rand() perchè statisticamente non garantisce casualità
    std::random_device device; // per il seeding
    std::default_random_engine gen{device()};
    std::uniform_int_distribution<int> dis{0,1};
    return dis(gen) & 1;  //AND tra '1' e l'intero random tra 0 e 1;
}