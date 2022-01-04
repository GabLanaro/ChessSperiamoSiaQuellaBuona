#include <iostream>
#include <string>
#include <cctype>
#include <ctime>
#include <fstream>
#include "game.h"
#include "board.h"

Game::Game(string mod)
{
    modalita = mod;
}


void Game::start()
{
    std::cout<<"\n*******************************************\n";
    gameIsOver = false; // verrà utilizzata nel ciclo do while per verificare che la partita non sia terminata
    int counterMosse{0}; //se la partita è computer vs computer, quando il counterMosse arriva a 200 la parita termina
    Board board;  //inizializzazione scacchiera

    std::ofstream fileLog; //creazione file di log
    fileLog.open("log.txt"); //il file di log rimarrà aperto durante tutta la partita.

    bool playerColor = randomColor(); // true=white, false=black
    Player player1(playerColor, false);      
    Player player2(!playerColor, false);       // player2 è un computer ed è creato in entrambe le modalità.
    if (tolower(modalita[0]) == 'p')
    {   // la modalità scelta è pc
        player1.setTipo(true); // player1 è umano
        if(player1.getColor()==0){
            std::cout<<"giocatore umano, ti è stato assegnato il colore nero,\ncomputer, muoverai la prima mossa.\n";
        }
        else{
            std::cout<<"giocatore umano, ti è stato assegnato il colore bianco,\nmuoverai la prima mossa.\n";
        }
    }
    Player *currentPlayer = (player1.getColor() == true) ? &player1 : &player2; // currentPlayer è un puntatore al player bianco
    // CICLO CHE VERIFICA SCACCO E SCACCOMATTO, CHIEDE MOSSA, LA EFFETTUA E CAMBIA TURNO.
    do
    {
        if (sottoScacco(*currentPlayer))
        {
            if (scaccoMatto(*currentPlayer))
                gameIsOver = true;
            else
                std::cout << "attenzione! Il tuo re è sottoscacco."<<std::endl;
        }
        // il re non è sottoscacco, currentPlayer inserisce mossa.
        bool done=false;
        while(!done){   //ciclo che itera finchè la mossa inserita è valida
            int rigaI,colonnaI,rigaF,colonnaF;
            std::tie(rigaI,colonnaI,rigaF,colonnaF)=currentPlayer->mossa();  //il giocatore di turno inserisce la mossa
            if(board.isMoveValid(rigaI,colonnaI,rigaF,colonnaF)){   //verifica della correttezza della mossa inserita
                board.spostaPezzo();
                std::cout<<"mossa effettuata:   "<<rigaI<<colonnaI<<" "<<rigaF<<colonnaF<<"\n";
                fileLog<<rigaI<<colonnaI<<" "<<rigaF<<colonnaF<<"\n";
                currentPlayer=(currentPlayer->getColor()==player1.getColor())? &player2 : &player1; //cambio turno giocatore
                done=true;  //esci dal ciclo
            }
        }
        counterMosse++;
        if(tolower(modalita[0])=='c' && counterMosse==200){
            std::cout<<"numero massimo di mosse raggiunto. La partita è annullata.";
            gameIsOver=true;
        }
        
    } while (!gameIsOver);
    fileLog.close(); //chiusura file di log al termine della partita
}


bool Game::randomColor()
{
    // true=white, false=black
    srand(time(NULL));   // seed
    bool x = rand() % 2; // numero intreo casuale tra 0 e 1
    return x & 1;        // funzione AND tra il numero casuale e 1
}


bool Game::sottoScacco(Player &p)
{
    return false;
}


bool Game::scaccoMatto(Player &p)
{
    return false;
}
