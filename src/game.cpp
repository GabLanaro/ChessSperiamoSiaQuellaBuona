#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>
#include <ctime>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
#include "game.h"
#include "board.h"
#include "player.h"

Game::Game(string mod)
{
    modalita = mod;
}

void Game::start()
{
    // Chrono per verificare statisticamente la patta
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<float> tempoMossa, tempoLim;

    srand(time(NULL));             // seed per generare mossa casuale del computer
    gameIsOver = false;            // verrà utilizzata nel ciclo do while per verificare che la partita non sia terminata
    int counterMosse{0};           // se la partita è computer vs computer, quando il counterMosse arriva a 200 la parita termina
    Board board;                   // inizializzazione scacchiera
    std::vector<string> vectBoard; // vector che contiene delle stringhe raffiguranti la board
    std::vector<int> vectVuoti_P;  // vector che contiene la somma delle posizioni vuote e degli indici dei pedoni
    string strBoard;               // stringhe raffiguranti la board
    int numVuoti_P;                // int corrispondente alla somma di caselle vuote nella board più la somma degli indici dei pedoni
    std::ofstream fileLog;         // creazione file di log
    fileLog.open("log.txt");       // il file di log rimarrà aperto durante tutta la partita.

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
    strBoard = creaStrBoard(board);
    vectBoard.push_back(strBoard);

    // CICLO CHE VERIFICA SCACCO E SCACCOMATTO, CHIEDE MOSSA, LA EFFETTUA E CAMBIA TURNO.
    do
    { // Verifica che il re del currentPlayer non sia sotto scacco o scacco matto
        if (sottoScacco(*currentPlayer, board))
        {
            if (scaccoMatto(*currentPlayer, board))
            {
                std::cout << "SCACCO MATTO -- partita terminata";
                gameIsOver = true;
            }
            else
                std::cout << "Attenzione! Il tuo re \212 sottoscacco." << std::endl;
        }
        bool done = false;
        if (gameIsOver == false)
        {
            // il re non è sottoscacco, currentPlayer inserisce mossa.
            start = std::chrono::system_clock::now();
            tempoLim = std::chrono::seconds(5);
            while (!done)
            {
                // ciclo che itera finchè la mossa inserita è valida
                int rigaI, colonnaI, rigaF, colonnaF;
                std::tie(colonnaI, rigaI, colonnaF, rigaF) = currentPlayer->mossa(board); // il giocatore di turno inserisce la mossa
                if (colonnaI == -1)
                {
                    std::cout << "La patta \212 stata accettata dal Computer\nLa partita si \212 conclusa con una PATTA";
                    gameIsOver = true;
                    break;
                }
                if ((arrocco(board, vectBoard, currentPlayer->getColor(), colonnaI)))
                {
                    std::cout << "Arrocco effettuato";
                    // cambia turno
                    break;
                }

                /*if (enPassant(board, rigaI, colonnaI, rigaF, colonnaF))
                {
                    done = true;
                }*/
                tempoMossa = end - start;

                if (currentPlayer->getTipo() == false) // Statisticamente il PC non ha trovato mosse valide, quindi non ce ne sono
                {
                    end = std::chrono::system_clock::now();
                    done = (tempoMossa > tempoLim) ? true : false;
                }
                if (isMoveValid(rigaI, colonnaI, rigaF, colonnaF, currentPlayer, board))
                { // verifica della correttezza della mossa inserita
                    board.spostaPezzo(rigaI, colonnaI, rigaF, colonnaF);
                    std::cout << "mossa effettuata:   " << rigaI << colonnaI << " " << rigaF << colonnaF << "\n";
                    fileLog << rigaI << colonnaI << " " << rigaF << colonnaF << "\n"; // scrive la mossa nel file di log
                    promozione(board, rigaF, colonnaF);
                    currentPlayer = (currentPlayer->getColor() == player1.getColor()) ? &player2 : &player1; // cambio turno giocatore
                    done = true;                                                                             // esci dal ciclo
                }
            }

            counterMosse++;
            // Creazione stringa che rappresenta la board e push nel vectBoard di stringhe
            strBoard = creaStrBoard(board);
            vectBoard.push_back(strBoard);

            // Conteggio indici dei pedoni + numero di caselle vuote e push nel vectVuoti_P di int
            numVuoti_P = contaVuoti_P(strBoard);
            vectVuoti_P.push_back(numVuoti_P);

            // Verifica patta
            if ((isPatta(vectBoard, vectVuoti_P, strBoard, counterMosse)) ||
                ((currentPlayer->getTipo() == false) && (tempoMossa > tempoLim)))
            {
                std::cout << "La partita si \212 conclusa con una PATTA";
                gameIsOver = true;
            }

            board.printScacchiera();

            if (tolower(modalita[0]) == 'c') // se la partita è tra due computer si attende 1 secondo tra una mossa e l'altra
            {
                this_thread::sleep_for(chrono::seconds(1));
            }
            if (tolower(modalita[0]) == 'c' && counterMosse == 100) // dopo 100 mosse la partita tra due computer termina
            {
                std::cout << "numero massimo di mosse raggiunto. La partita \212 annullata.";
                gameIsOver = true;
            }
        }

    } while (!gameIsOver);
    fileLog.close(); // chiusura file di log al termine della partita
}

bool Game::randomColor()
{
    // true=white, false=black
    srand(time(NULL));   // seed
    bool x = rand() % 2; // numero intero casuale tra 0 e 1
    return x;            // Ho tolto l'AND tra x & 1
}

bool Game::isMoveValid(int rigaI, int colonnaI, int rigaF, int colonnaF, Player *currentPlayer, Board &board)
{
    // 4 check di validità che valgono per tutti i pezzi.
    // 0)controllo che la casella scelta non sia vuota
    if (board.getPezzo(rigaI, colonnaI) == NULL)
    {
        if (currentPlayer->getTipo() == true)
            cout << "la casella scelta \212 vuota!\n";
        return false;
    }
    // 1)controllo che il pezzo scelto sia di current player
    if (currentPlayer->getColor() != board.getPezzo(rigaI, colonnaI)->getColor())
    {
        if (currentPlayer->getTipo() == true)
            cout << "il pezzo scelto \212 dell'altro giocatore!\n";
        return false;
    }

    // 2)controllo che la casella d'arrivo non sia occupata da un pezzo di currentPlayer
    /*if (board.getPezzo(rigaF, colonnaF) != NULL && currentPlayer->getColor() == board.getPezzo(rigaF, colonnaF)->getColor())
    {
        if(currentPlayer->getTipo()==true)
        cout << "la casella d'arrivo \212 occupata da un tuo pezzo!\n";
        return false;
    }*/

    // check di validità del pezzo in particolare
    if (board.getPezzo(rigaI, colonnaI)->isValid(rigaI, colonnaI, rigaF, colonnaF, board) == false)
    {
        if (currentPlayer->getTipo() == true)
            cout << "il pezzo scelto non puo muoversi in quella direzione\n";
        return false;
    }

    // 3)controllo che la mossa non metta il re di currentPlayer sottoscacco effettuando temporaneamente la mossa
    Pezzo *temp = board.getPezzo(rigaF, colonnaF);
    Pezzo *iniziale = board.getPezzo(rigaI, colonnaI);
    board.setPezzo(iniziale, rigaF, colonnaF); // il pezzo da muovere viene messo temporaneamente nella casella finale
    board.setPezzo(NULL, rigaI, colonnaI);     // la casella finale viene messa temporaneamente NULL.
    if (sottoScacco(*currentPlayer, board))
    {
        cout << "la mossa mette il tuo re sottoscacco*********************************************\n";
        // ripristino la mosssa
        board.setPezzo(temp, rigaF, colonnaF);
        board.setPezzo(iniziale, rigaI, colonnaI);
        return false;
    }
    // anche se non è sottoscacco ripristino la mossa
    board.setPezzo(temp, rigaF, colonnaF);
    board.setPezzo(iniziale, rigaI, colonnaI);

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
                    /*if ((pez->getName() == 'r') || (pez->getName() == 'R'))
                    {
                        rigRe = rigCurr;
                        colRe = colCurr;
                    }*/
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
    {
        for (int colCurr = 0; colCurr < 8; colCurr++)
        {
            if (b.getPezzo(rigCurr, colCurr) != NULL)
            {
                Pezzo *pez = b.getPezzo(rigCurr, colCurr);
                // Prendo un pezzo del player
                if ((pez->getColor() == p.getColor()))
                {
                    // Guardo se questo per qualche mossa può risolvere lo scacco al Re
                    for (int rigNew = 0; rigNew < 8; rigNew++)
                    {
                        for (int colNew = 0; colNew < 8; colNew++)
                        {
                            Pezzo *nuovoPez = b.getPezzo(rigNew, colNew);
                            // Simula la mossa e guarda se è possibile risolvere lo scacco
                            if (isMoveValid(rigCurr, colCurr, rigNew, colNew, &p, b))
                            {
                                // Dentro isMoveValid c'è già il controllo e la simulazione della mossa
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }
    // Se non trovo nessuna mossa che risolve lo scacco significa che è scacco matto
    return true;
}

void Game::promozione(Board &b, int rigaF, int colonnaF)
{
    string scelta;
    bool sceltaValida = false;
    Pezzo *pez = b.getPezzo(rigaF, colonnaF);
    if (((pez->getName() == 'p') && (rigaF == 7)) || ((pez->getName() == 'P') && (rigaF == 0)))
    {
        // delete pedone
        std::cout << "Inserisci l'iniziale del pezzo con cui vorresti sostituire il pedone: ";
        do
        {
            getline(cin, scelta);
            switch (scelta[0])
            { // mettere anche qua il controllo che non cambia tra maiuscole e minuscole?
            case 't':
                if (pez->getColor() == true)
                { // se è bianco
                    b.setPezzo(new Torre(true, 't'), 7, colonnaF);
                }
                else if (pez->getColor() == false)
                { // ha senso usare else if o basta mettere else?
                    b.setPezzo(new Torre(false, 'T'), 0, colonnaF);
                }
                sceltaValida = true;
                break;

            case 'c':
                if (pez->getColor() == true)
                { // se è bianco
                    b.setPezzo(new Cavallo(true, 'c'), 7, colonnaF);
                }
                else if (pez->getColor() == false)
                { // ha senso usare else if o basta mettere else?
                    b.setPezzo(new Cavallo(false, 'C'), 0, colonnaF);
                }
                sceltaValida = true;
                break;

            case 'a':
                if (pez->getColor() == true)
                { // se è bianco
                    b.setPezzo(new Alfiere(true, 'a'), 7, colonnaF);
                }
                else if (pez->getColor() == false)
                { // ha senso usare else if o basta mettere else?
                    b.setPezzo(new Alfiere(false, 'A'), 0, colonnaF);
                }
                sceltaValida = true;
                break;

            case 'd':
                if (pez->getColor() == true)
                { // se è bianco
                    b.setPezzo(new Regina(true, 'd'), 7, colonnaF);
                }
                else if (pez->getColor() == false)
                { // ha senso usare else if o basta mettere else?
                    b.setPezzo(new Regina(false, 'D'), 0, colonnaF);
                }
                sceltaValida = true;
                break;

            case 'p':
                if (pez->getColor() == true)
                { // se è bianco
                    b.setPezzo(new Pedone(true, 'p'), 7, colonnaF);
                }
                else if (pez->getColor() == false)
                { // ha senso usare else if o basta mettere else?
                    b.setPezzo(new Pedone(false, 'P'), 0, colonnaF);
                }
                sceltaValida = true;
                break;
            }
            if (sceltaValida == false)
            {
                std::cout << "Scelta non valida, riprova" << endl;
            }
        } while (sceltaValida == false);
    }
}

bool Game::enPassant(Board &b, int rigaI, int colonnaI, int rigaF, int colonnaF)
{
    Pezzo *PezzoIniziale = b.getPezzo(rigaI, colonnaI); // Creo un puntatore al pezzo iniziale
    Pezzo *PezzoFinale = b.getPezzo(rigaF, colonnaF);   // Creo un puntatore al pezzo d'arrivo
    if ((rigaI == 4) && (PezzoFinale == NULL) && (PezzoIniziale->getName() == 'p'))
    {
        if ((colonnaF == PezzoIniziale->getColonnaPed()) && (rigaF == PezzoIniziale->getRigaPed() + 1))
        {
            return true;
        }
    }
    else if ((rigaI == 3) && (PezzoFinale == NULL) && (PezzoIniziale->getName() == 'P'))
    {
        if ((colonnaF == PezzoIniziale->getColonnaPed()) && (rigaF == PezzoIniziale->getRigaPed() - 1))
        {
            return true;
        }
    }

    return false;
}

bool Game::arrocco(Board &b, vector<string> vectBoard, bool color, int lato)
{
    string strBoard;
    if ((color == true) && (lato == -2)) // Arrocco bianco a destra
    {
        for (int i = 0; i < vectBoard.size(); i++)
        {
            strBoard = vectBoard[i];
            if ((strBoard[7] != 't') && strBoard[4] == 'r')
            {
                b.spostaPezzo(0, 4, 0, 6); // Sposta Re in G1
                b.spostaPezzo(0, 7, 0, 5); // Sposta torre in F1
                return true;
            }
        }
    }
    else if ((color == true) && (lato == -3)) // Arrocco bianco a sinistra
    {
        for (int i = 0; i < vectBoard.size(); i++)
        {
            strBoard = vectBoard[i];
            if (strBoard[0] != 't' && strBoard[4] == 'r')
            {
                b.spostaPezzo(0, 4, 0, 2); // Sposta Re da E1 a C1
                b.spostaPezzo(0, 0, 0, 3); // Sposta torre da A1 a D1
                return true;
            }
        }
    }
    else if ((color == false) && (lato == -2)) // Arrocco nero a destra
    {
        for (int i = 0; i < vectBoard.size(); i++)
        {
            strBoard = vectBoard[i];
            if (strBoard[63] != 'T' && strBoard[60] == 'R')
            {
                b.spostaPezzo(7, 4, 7, 6); // Sposta Re da E8 a G8
                b.spostaPezzo(7, 7, 7, 5); // Sposta torre da H8 a F8
                return true;
            }
        }
    }
    else if ((color == false) && (lato == -3)) // Arrocco nero a sinistra
    {
        for (int i = 0; i < vectBoard.size(); i++)
        {
            strBoard = vectBoard[i];
            if (strBoard[56] == 'T' && strBoard[60] == 'R')
            {
                b.spostaPezzo(7, 4, 7, 2); // Sposta Re da E8 a C8
                b.spostaPezzo(7, 7, 7, 3); // Sposta torre da H8 a D8
                return true;
            }
        }
    }
    return false;
}

string Game::creaStrBoard(Board &b)
{

    string nomePezzo;
    string strBoard;

    for (int rigCurr = 0; rigCurr < 8; rigCurr++)
    {
        for (int colCurr = 0; colCurr < 8; colCurr++)
        { // Prendo il pezzo corrente e metto il suo nome nella stringa
            if (b.getPezzo(rigCurr, colCurr) != NULL)
            {
                Pezzo *pez = b.getPezzo(rigCurr, colCurr);
                nomePezzo = pez->getName();
                strBoard.append(nomePezzo);
            }
            else
            { // 0 rappresenta nella stringa una posizione vuota
                strBoard.append("0");
            }
        }
    }
    return strBoard;
}

int Game::contaVuoti_P(string strBoard)
{
    int numVuoti{0}; // Numero di zeri nella strBoard ovvero numero di caselle vuote nella board
    int indiciP{0};  // Somma indici delle posizioni dei pedoni
    // conto il numero di vuoti e l'indice dei pedoni nella stringa che rappresenta la scacchiera
    for (int i = 0; i < strBoard.size(); i++)
    {
        if (strBoard[i] == '0')
        {
            numVuoti++;
        }
        else if (strBoard[i] == 'p' || strBoard[i] == 'P')
        {
            // indiciP contiene un numero uguale alla somma degli
            // indici dei pedoni presenti nella scacchiera
            // se uno dei pedoni presenti viene spostato allora cambierà anche indiciP
            indiciP += i;
        }
    }
    return numVuoti + indiciP;
}

bool Game::isPatta(vector<string> vectBoard, vector<int> vectVuoti_P, string strBoard, int countmosse)
{
    //  PRIMA CONDIZIONE VERIFICATA IN MAIN

    //  SECONDA CONDIZIONE: Posizione ripetuta per tre volte
    // controllo occorrenza di strBoard nel vectBoard
    if (std::count(vectBoard.begin(), vectBoard.end(), vectBoard[countmosse - 1]) == 3)
    {
        return true;
    }

    // TERZA CONDIZIONE: 50 mosse consecutive senza che vengano mangiati pezzi o mossi pedoni
    // controllo se ci sono 50 elementi uguali consecutivi in vectVuoti_P
    int mossaPat{0};
    for (int i = 1; i < vectVuoti_P.size(); i++)
    {
        if (vectVuoti_P[i - 1] == vectVuoti_P[i])
        {
            mossaPat++;
        }
        else
        {
            mossaPat = 0;
        }
        if (mossaPat == 50)
        {
            return true;
        }
    }

    // QUARTA CONDIZIONE: posizione morta, non ci sono abbastanza pezzi per forzare uno scacco matto
    if (((std::count(strBoard.begin(), strBoard.end(), 'c') == 1) ||
         (std::count(strBoard.begin(), strBoard.end(), 'C') == 1) ||
         (std::count(strBoard.begin(), strBoard.end(), 'a') == 1) ||
         std::count(strBoard.begin(), strBoard.end(), 'A')) &&
        vectVuoti_P[countmosse - 1] == 61)
    {
        return true;
    }

    return false;
}