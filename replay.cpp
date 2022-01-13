#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <chrono>
#include <thread>

using namespace std;

// funzione che stampa la configurazione della scacchiera dopo una mossa
void printFrame(int r1, int c1, int r2, int c2, array<array<char, 8>, 8> &b)
{ // effettuo mossa
    // cout<<r1<<c1<<"***"<<r2<<c2<<endl;
    // cout<<b[r2][c2]<<"***"<<b[r1][c1]<<endl;
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
            printf("%c ", b[i][j]);
        }
        indexRiga--;
        cout << endl;
    }
    printf("%s", "\n   A B C D E F G H\n\n");
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
    string fileLog = argv[2];
    string fileOutput = argv[3];
    // controllo che il primo argomento inserito da linea di comando sia valido
    if (tipoReplay != "v" && tipoReplay != "f")
    {
        cout << "Il comando inserito per il replay non è valido,\nSi riesegua il programma usando come argomento \"v [nome_file_log]\" o \" f [nome_file_log] [nome_file_output_replay]\"\n";
        return 0;
    }
    if (tipoReplay == "v")
    { // il replay viene stampato a video
        string line;
        ifstream chessMoves;
        chessMoves.open(fileLog);
        while (getline(chessMoves, line))
        { // itera finchè non ci sono più righe da leggere nel file
            cout << line[0] << line[1] << line[3] << line[4] << endl;
            printFrame(line[0] - '0', line[1] - '0', line[3] - '0', line[4] - '0', charBoard); // stampa frame scacchiera (si noti che i char sono convertiti in int con es. line[1]-'0')
            this_thread::sleep_for(chrono::seconds(2));                                        // attende 1 secondo tra un frame e il successivo
        }
    }
    else
    { // il replay viene stampato su un altro file
        cout << "x";
    }

    return 0;
}
