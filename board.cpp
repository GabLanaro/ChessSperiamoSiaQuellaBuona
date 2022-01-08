#include "board.h"
#include <iostream>
#include <iterator>
#include <algorithm>
using namespace std;

Board::Board()
{
    // inizializzo una scacchiera vuota
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[i][j] = NULL;
        }
    }
    // inserisco nella matrice i puntatori ai pezzi bianchi
    setPezzo(new Torre(true), 0, 0);
    setPezzo(new Cavallo(true), 0, 1);
    setPezzo(new Alfiere(true), 0, 2);
    setPezzo(new Regina(true), 0, 3);
    setPezzo(new Re(true), 0, 4);
    setPezzo(new Alfiere(true), 0, 5);
    setPezzo(new Cavallo(true), 0, 6);
    setPezzo(new Torre(true), 0, 7);
    for (int i = 0; i <= 7; i++)
    {
        setPezzo(new Pedone(true), 1, i);
    }
    // inserisco nella matrice i puntatori ai pezzi neri
    setPezzo(new Torre(false), 7, 0);
    setPezzo(new Cavallo(false), 7, 1);
    setPezzo(new Alfiere(false), 7, 2);
    setPezzo(new Regina(false), 7, 3);
    setPezzo(new Re(false), 7, 4);
    setPezzo(new Alfiere(false), 7, 5);
    setPezzo(new Cavallo(false), 7, 6);
    setPezzo(new Torre(false), 7, 7);
    for (int i = 0; i <= 7; i++)
    {
        setPezzo(new Pedone(false), 6, i);
    }
}

void Board::printScacchiera()
{
    // cout<<board.nome;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] == NULL)
            {
                cout << " ";
            }
            else
            {
                // cout << board[i][j]->getNome();
            }
        }
        cout << endl;
    }
}

void Board::spostaPezzo()
{
    // swap dei pezzi + eliminazione eventuale pezzo
}

bool Board::isMoveValid(int rigaI, int colonnaI, int rigaF, int colonnaF)
{
    return true;
    // check generali:
    //è un pezzo tuo? a[rigaI][colonnaI].getColor()==currentPlayer.getColor()
    // la casella d'arrivo è occupata da un tuo pezzo?
    // la mossa mette il tuo re sottoscacco?
}

void Board::setPezzo(Pezzo *P, int rig, int col) // inserisce il pezzo nella scacchiera
{
    board[rig][col] = P;
}

Pezzo *Board::getPezzo(int rig, int col) // restituisce il puntatore al pezzo in quella posizione della scacchiera
{
    return board[rig][col];
}