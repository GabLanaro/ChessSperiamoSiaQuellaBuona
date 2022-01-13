#include <iostream>
#include <string>
#include <cctype>
#include <ctime>
#include <fstream>
#include "game.h"
#include "board.h"
#include "player.h"

Game::Game(string mod)
{
    modalita = mod;
}

void Game::start()
{
    std::cout << "\n*******************************************\n";
    gameIsOver = false;  // verrà utilizzata nel ciclo do while per verificare che la partita non sia terminata
    int counterMosse{0}; // se la partita è computer vs computer, quando il counterMosse arriva a 200 la parita termina
    Board board;         // inizializzazione scacchiera

    std::ofstream fileLog;   // creazione file di log
    fileLog.open("log.txt"); // il file di log rimarrà aperto durante tutta la partita.

    bool playerColor = randomColor(); // true=white, false=black
    Player player1(playerColor, false);
    Player player2(!playerColor, false); // player2 è un computer ed è creato in entrambe le modalità.
    if (tolower(modalita[0]) == 'p')
    {                          // la modalità scelta è pc
        player1.setTipo(true); // player1 è umano
        if (player1.getColor() == 0)
        {
            std::cout << "giocatore umano, ti \212 stato assegnato il colore nero,\ncomputer, muoverai la prima mossa.\n";
        }
        else
        {
            std::cout << "giocatore umano, ti \212 stato assegnato il colore bianco,\nmuoverai la prima mossa.\n";
        }
    }
    Player *currentPlayer = (player1.getColor() == true) ? &player1 : &player2; // currentPlayer è un puntatore al player bianco
    // CICLO CHE VERIFICA SCACCO E SCACCOMATTO, CHIEDE MOSSA, LA EFFETTUA E CAMBIA TURNO.
    do
    {
        if (sottoScacco(*currentPlayer, board))
        {
            if (scaccoMatto(*currentPlayer))
                gameIsOver = true;
            else
                std::cout << "attenzione! Il tuo re \212 sottoscacco." << std::endl;
        }
        // il re non è sottoscacco, currentPlayer inserisce mossa.
        bool done = false;
        while (!done)
        { // ciclo che itera finchè la mossa inserita è valida
            int rigaI, colonnaI, rigaF, colonnaF;
            std::tie(colonnaI, rigaI, colonnaF, rigaF) = currentPlayer->mossa(board); // il giocatore di turno inserisce la mossa
            if (board.isMoveValid(rigaI, colonnaI, rigaF, colonnaF, currentPlayer))
            { // verifica della correttezza della mossa inserita
                cout<<"XXXX";
                board.spostaPezzo(rigaI, colonnaI, rigaF, colonnaF);
                std::cout << "mossa effettuata:   " << colonnaI << rigaI << " " << colonnaF << rigaF << "\n"; // perchè prima colonna e poi riga e non viceversa?
                fileLog << rigaI << colonnaI << " " << rigaF << colonnaF << "\n";                             // scrive la mossa nel file di log
                currentPlayer = (currentPlayer->getColor() == player1.getColor()) ? &player2 : &player1;      // cambio turno giocatore
                done = true;  // esci dal ciclo
                board.printScacchiera(); cout<<endl;
            }
        }
        counterMosse++;
        board.printScacchiera();
        if (tolower(modalita[0]) == 'c' && counterMosse == 200)
        {
            std::cout << "numero massimo di mosse raggiunto. La partita è annullata.";
            gameIsOver = true;
        }
        if (counterMosse == 10)
            gameIsOver = true;

    } while (!gameIsOver);
    fileLog.close(); // chiusura file di log al termine della partita
}

bool Game::randomColor()
{
    // true=white, false=black
    srand(time(NULL));   // seed
    bool x = rand() % 2; // numero intreo casuale tra 0 e 1
    return x & 1;        // funzione AND tra il numero casuale e 1
}

bool Game::sottoScacco(Player &p, Board &b)
{
    // PRIMA PARTE: Cerco il Re del current Player
    int rigRe = 1;
    int colRe = 1;
    // Scorro tutte le caselle della scacchiera
    for (int rigCurr = 0; rigCurr < 8; rigCurr++)
    {
        for (int colCurr = 0; colCurr < 8; colCurr++)
        {
            // ispeziono il pezzo preso per vedere se è il re cercato
            if (b.getPezzo(rigCurr, colCurr) != NULL)
            {
                Pezzo *pez = b.getPezzo(rigCurr, colCurr);
                if (p.getColor() == pez->getColor())
                {
                    if (pez->getName() == 'r' && p.getColor() == true) // se bianco
                    {
                        rigRe = rigCurr;
                        colRe = colCurr;
                    }
                    else if (pez->getName() == 'R' && p.getColor() == false) // se nero
                    {
                        rigRe = rigCurr;
                        colRe = colCurr;
                    }
                }
            }
        }
    }
    /*
        // SECONDA PARTE: Vedo se i pezzi avversari possono mangiare il re trovato
        for (int rigCurr = 0; rigCurr < 8; rigCurr++)
        {
            for (int colCurr = 0; colCurr < 8; colCurr++)
            {
                if (b.getPezzo(rigCurr, colCurr) != NULL)
                {
                    Pezzo *pez = b.getPezzo(rigCurr, colCurr);
                    if (p.getColor() != pez->getColor())
                    {
                        if (pez->isValid(rigCurr, rigRe, colCurr, colRe))
                        {
                            return true;
                        }
                    }
                }
            }
        }
     */
    return false;
}

bool Game::scaccoMatto(Player &p)
{
    // Guardo tutti i pezzi doppio for
    // prendo solo i pezzi del currPlayer e non nulli nella scacchiera con if colore e !=null
    // similo delle mosse con il pezzo preso e vedo se riesce a risolvere lo scacco
    // quando non ho più pezzi da verificare allora return true
    return false;
}
