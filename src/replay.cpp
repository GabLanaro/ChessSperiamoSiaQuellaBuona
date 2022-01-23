// FILIPPO MORBIATO

#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <chrono>
#include <thread>
#include <stdio.h>

using namespace std;

// stampa su schermo la configurazione della scacchiera dopo una mossa
void printFrameOnScreen(int r1, int c1, int r2, int c2, char ctrlPromo, array<array<char, 8>, 8> &b)
{ // effettuo mossa
    b[r2][c2] = b[r1][c1];
    b[r1][c1] = ' ';
    // stampo configurazione scacchiera
    cout << endl;
    int indexRiga = 8;
    for (int i = 7; i >= 0; i--)
    {
        printf("%d  ", indexRiga);
        for (int j = 0; j < 8; j++)
        {
            if (ctrlPromo == 'D')
            {
                if (b[r2][c2] == 'p')
                {
                    b[r2][c2] = 'd';
                }
                else if (b[r2][c2] == 'P')
                {
                    b[r2][c2] = 'D';
                }
            }
            printf("%c ", b[i][j]);
        }
        indexRiga--;
        cout << endl;
    }
    printf("%s", "\n   A B C D E F G H\n\n");
}

// stampa su file la configurazione della scacchiera dopo una mossa
void printFrameOnFile(int r1, int c1, int r2, int c2, char ctrlPromo, array<array<char, 8>, 8> &b, FILE *fileOut)
{ // effettuo mossa
    b[r2][c2] = b[r1][c1];
    b[r1][c1] = ' ';
    // stampo configurazione scacchiera
    fprintf(fileOut, "\n");
    int indexRiga = 8;
    for (int i = 7; i >= 0; i--)
    {
        fprintf(fileOut, "%d  ", indexRiga);
        for (int j = 0; j < 8; j++)
        {
            if (ctrlPromo == 'D')
            {
                if (b[r2][c2] == 'p')
                {
                    b[r2][c2] = 'd';
                }
                else if (b[r2][c2] == 'P')
                {
                    b[r2][c2] = 'D';
                }
            }
            fprintf(fileOut, "%c ", b[i][j]);
        }
        indexRiga--;
        fprintf(fileOut, "\n");
    }
    fprintf(fileOut, "%s", "\n   A B C D E F G H\n\n");
}

int main(int argc, char *argv[])
{
    array<array<char, 8>, 8> charBoard{// la scacchiera è una matrice di char
                                       't', 'c', 'a', 'd', 'r', 'a', 'c', 't',
                                       'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
                                       ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                                       ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                                       ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                                       ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                                       'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
                                       'T', 'C', 'A', 'D', 'R', 'A', 'C', 'T'};

    string tipoReplay = argv[1];
    string nomeFileLog = argv[2];
    string nomeFileOutput;
    if (argv[3] != NULL)
    {
        nomeFileOutput = argv[3];
    }
    // controllo che il primo argomento inserito da linea di comando sia valido
    if (tipoReplay != "v" && tipoReplay != "f")
    {
        cout << "Il comando inserito per il replay non \212 valido,\nSi riesegua il programma usando come argomento \"v [nome_file_log]\" o \" f [nome_file_log] [nome_file_output_replay]\"\n";
        return 0;
    }

    FILE *pfileOut; // puntatore di tipo FILE utilizzato per aprire e chiudere il file di output

    if (tipoReplay == "f")
    {
        pfileOut = fopen(nomeFileOutput.c_str(), "w"); // il file di output rimarrà aperto durante tutta la esecuzione.
        cout << "la partita registrata nel file di log " << nomeFileLog << " \212 stata stampata nel file " << nomeFileOutput;
    }

    string line;
    ifstream chessMoves;
    chessMoves.open(nomeFileLog); // apro il file da cui leggere le mosse
    while (getline(chessMoves, line))
    { // itera finchè non ci sono più righe da leggere nel file

        if (tipoReplay == "v")
        {
            printFrameOnScreen(line[0] - '0', line[1] - '0', line[3] - '0', line[4] - '0', line[5], charBoard); // stampa frame scacchiera (si noti che i char sono convertiti in int con es. line[1]-'0')
            this_thread::sleep_for(chrono::seconds(2));                                                         // attende 2 secondi tra un frame e il successivo
        }
        else
        {
            printFrameOnFile(line[0] - '0', line[1] - '0', line[3] - '0', line[4] - '0', line[5], charBoard, pfileOut); // stampa frame scacchiera su file di output
        }
    }
    if (tipoReplay == "f")
    {
        fclose(pfileOut); // chiudo file su cui è stata stampata la partita
    }

    return 0;
}