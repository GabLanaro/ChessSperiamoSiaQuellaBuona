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
    srand(time(NULL));   // seed per generare mossa casuale del computer
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
            if (scaccoMatto(*currentPlayer, board))
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
            if (isMoveValid(rigaI, colonnaI, rigaF, colonnaF, currentPlayer, board))
            { // verifica della correttezza della mossa inserita
                board.spostaPezzo(rigaI, colonnaI, rigaF, colonnaF);
                std::cout << "mossa effettuata:   " << rigaI << colonnaI << " " << rigaF << colonnaF << "\n";
                fileLog << rigaI << colonnaI << " " << rigaF << colonnaF << "\n";                        // scrive la mossa nel file di log
                currentPlayer = (currentPlayer->getColor() == player1.getColor()) ? &player2 : &player1; // cambio turno giocatore
                done = true;                                                                             // esci dal ciclo
            }
        }
        counterMosse++;
        board.printScacchiera();
        if (tolower(modalita[0]) == 'c' && counterMosse == 100)
        {
            std::cout << "numero massimo di mosse raggiunto. La partita \212 annullata.";
            gameIsOver = true;
        }

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

bool Game::isMoveValid(int rigaI, int colonnaI, int rigaF, int colonnaF, Player *currentPlayer, Board &board)
{
    // 4 check di validità che valgono per tutti i pezzi.
    // 0)controllo che la casella scelta non sia vuota
    if (board.getPezzo(rigaI, colonnaI) == NULL)
    {
        // if(currentPlayer->getTipo()==true)
        cout << "la casella scelta \212 vuota!\n";
        return false;
    }
    // 1)controllo che il pezzo scelto sia di current player
    if (currentPlayer->getColor() != board.getPezzo(rigaI, colonnaI)->getColor())
    {
        // if(currentPlayer->getTipo()==true)
        cout << "il pezzo scelto \212 dell'altro giocatore!\n";
        return false;
    }
    // 2)controllo che la casella d'arrivo non sia occupata da un pezzo di currentPlayer
    if (board.getPezzo(rigaF, colonnaF) != NULL && currentPlayer->getColor() == board.getPezzo(rigaF, colonnaF)->getColor())
    {
        // if(currentPlayer->getTipo()==true)
        cout << "la casella d'arrivo \212 occupata da un tuo pezzo!\n";
        return false;
    }
    // 3)controllo che la mossa non metta il re di currentPlayer sottoscacco effettuando temporaneamente la mossa
    Pezzo *temp = board.getPezzo(rigaF, colonnaF);
    Pezzo *iniziale = board.getPezzo(rigaI, colonnaI);
    board.setPezzo(iniziale, rigaF, colonnaF); // il pezzo da muovere viene messo temporaneamente nella casella finale
    board.setPezzo(NULL, rigaI, colonnaI);     // la casella finale viene messa temporaneamente NULL.
    if (sottoScacco(*currentPlayer, board))
    {
        cout << "la mossa mette il tuo re sottoscacco\n";
        // ripristino la mosssa
        board.setPezzo(temp, rigaF, colonnaF);
        board.setPezzo(iniziale, rigaI, colonnaI);
        return false;
    }
    // anche se non è sottoscacco ripristino la mossa
    board.setPezzo(temp, rigaF, colonnaF);
    board.setPezzo(iniziale, rigaI, colonnaI);

    // check di validità del pezzo in particolare
    if (board.getPezzo(rigaI, colonnaI)->isValid(rigaI, colonnaI, rigaF, colonnaF, board) == false)
    {
        // if(currentPlayer->getTipo()==true)
        cout << "il pezzo scelto non puo muoversi in quella direzione\n";
        return false;
    }

    return true;
}

bool Game::sottoScacco(Player &p, Board &b)
{
    // PRIMA PARTE: Cerco il Re del current Player
    int rigRe;
    int colRe;
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
                    if (pez->isValid(rigCurr, colCurr, rigRe, colRe, b))
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool Game::scaccoMatto(Player &p, Board &b)
{
    // Ritorna true se il giocatore p è sotto scacco matto

    // <guardo> tutti gli scacchi uno alla volta
    for (int rigCurr = 0; rigCurr < 8; rigCurr++)
        for (int colCurr = 0; colCurr < 8; colCurr++)
        {
            Pezzo *pez = b.getPezzo(rigCurr, colCurr);
            // Prendo un pezzo del player
            if ((pez != NULL) && (pez->getColor() == p.getColor()))
            {
                // Guardo se questo per qualche mossa può risolvere lo scacco al Re
                for (int rigNew = 0; rigNew < 8; rigNew++)
                    for (int colNew = 0; colNew < 8; colNew++)
                    {
                        Pezzo *nuovoPez = b.getPezzo(rigNew, colNew);
                        // Simula la mossa e guarda se è possibile risolvere lo scacco
                        if (isMoveValid(rigCurr, colCurr, rigNew, colNew, &p, b))
                        {
                            b.setPezzo(nuovoPez, rigNew, colNew);
                            b.setPezzo(NULL, rigCurr, colCurr);
                            // Lo scacco non è stato risolto quindi annullo la mossa
                            if (!sottoScacco(p, b))
                            {
                                b.setPezzo(nuovoPez, rigNew, colNew);
                                b.setPezzo(pez, rigCurr, colCurr);
                                return false;
                            }
                            // Lo scacco non è stato risolto quindi annullo la mossa
                            // simulo un'altra mossa
                            else
                            {
                                b.setPezzo(nuovoPez, rigNew, colNew);
                                b.setPezzo(pez, rigCurr, colCurr);
                            }
                        }
                    }
            }
        }
    // Se non trovo nessuna mossa che risolve lo scacco significa che è scacco matto
    return true;
}