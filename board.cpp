#include "board.h"
#include <iostream>
#include <iterator>
#include <algorithm>
using namespace std;

Board::Board()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[i][j] = NULL;
        }
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
                cout << board[i][j]->getNome();
            }
        }
        cout << endl;
    }
}

void Board::spostaPezzo()
{
    //swap dei pezzi + eliminazione eventuale pezzo
}

bool Board::isMoveValid(int rigaI,int colonnaI,int rigaF,int colonnaF)
{
    return true;
}