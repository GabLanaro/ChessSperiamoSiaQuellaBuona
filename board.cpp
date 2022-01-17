#include <cstdio>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include "board.h"
#include "player.h"
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
    setPezzo(new Torre(true,'t'), 0, 0);
    setPezzo(new Cavallo(true,'c'), 0, 1);
    setPezzo(new Alfiere(true,'a'), 0, 2);
    setPezzo(new Regina(true,'d'), 0, 3);
    setPezzo(new Re(true,'r'), 0, 4);
    setPezzo(new Alfiere(true,'a'), 0, 5);
    setPezzo(new Cavallo(true,'c'), 0, 6);
    setPezzo(new Torre(true,'t'), 0, 7);
    /*for (int i = 0; i <= 7; i++)
    {
        setPezzo(new Pedone(true,'p'), 1, i);
    }*/
    // inserisco nella matrice i puntatori ai pezzi neri
    //setPezzo(new Torre(false,'T'), 7, 0);
    //setPezzo(new Cavallo(false,'C'), 7, 1);
    //setPezzo(new Alfiere(false,'A'), 7, 2);
    //setPezzo(new Regina(false,'D'), 7, 3);
    setPezzo(new Re(false,'R'), 7, 4);
    //setPezzo(new Alfiere(false,'A'), 7, 5);
    //setPezzo(new Cavallo(false,'C'), 7, 6);
    //setPezzo(new Torre(false,'T'), 7, 7);
    /*for (int i = 0; i <= 7; i++)
    {
        setPezzo(new Pedone(false,'P'), 6, i);
    }*/
}

void Board::printScacchiera()
{
    cout << endl;
    int indexRiga = 8;
    for (int i = 7; i >= 0; i--)
    {
        printf("%d  ", indexRiga);
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] == NULL)
            {
                printf("%c ", ' ');
            }
            else
            {
                printf("%c ", board[i][j]->getName());
            }
        }
        indexRiga--;
        cout << endl;
    }
    printf("%s", "\n   A B C D E F G H\n\n");
}

void Board::spostaPezzo(int rigaI, int colonnaI, int rigaF, int colonnaF)
{
    // swap dei pezzi
    Pezzo* temp=board[rigaF][colonnaF];
    board[rigaF][colonnaF] = board[rigaI][colonnaI];
    board[rigaI][colonnaI] = NULL;

    //DELETE QUA? mettere if per vedere se casella d'arrivo è null.
    if(temp!=NULL){
            cout<<temp->getName()<<"\n";
            delete temp;
            cout<<temp->getName()<<endl;
    }
}


void Board::setPezzo(Pezzo *P, int rig, int col) // inserisce il pezzo nella scacchiera
{
    board[rig][col] = P;
}

Pezzo *Board::getPezzo(int rig, int col) const // restituisce il puntatore al pezzo in quella posizione della scacchiera
{
    return board[rig][col];
}