#include "pezzo.h"

char Pezzo::getName() const{
    return name;
}

bool Pezzo::getColor() const{
    return color;
}

//Pedone

Pedone::Pedone(bool col){
    color=col;
    if(color==true){
        name='p';
    }
    else{
        name='P';
    }
    //funzione chooseName?
}

bool Pedone::isValid(int ri, int ci, int rf, int cf){
}

/*
#include <iostream>
#include <string>

#define N 8

using namespace std;

bool isValid(int rIni, int cIni, int rFin, int cFin, bool valido, char nome,int a[N][N]);

int main()
{
    int ri=1;
    int ci=0;
    int rf=2;
    int cf=0;
    bool valid=false;
    char name='p';
    string capo="\n";
    int arr[N][N];
    for (int i = 0; i < 8; i++)
    {
            for (int j = 0; j < 8; j++)
        {
            arr[i][j] = 0;
        }
    }
    
    cout << capo;
    cout << isValid(ri,ci,rf,cf,valid,name,arr);
    cout << capo;
    cout << valid;

    return 0;
}

bool isValid(int rIni, int cIni, int rFin, int cFin, bool valido, char nome,int a[N][N]){
    if(nome=='p'){ //Se è bianco
        if((rFin==rIni+1) && (cFin==cIni)){ //Se la mossa che sta facendo è andare avanti di una cella
            if(a[rFin][cFin]==0){ //Se nella cella in cui si sposta non c'è nulla
                valido=true; //Allora la mossa è valida
            }
        }
        
        if((rIni==1) && (rFin==3) && (cFin==cIni)){ //Se la mossa che sta facendo è la prima , può andare avanti di due celle
            if(a[rFin][cFin]==0){ //Se nella cella in cui si sposta non c'è nulla
                valido=true; //Allora la mossa è valida
            }
        }
        
        if((rFin==rIni+1) && (cFin==cIni+1) || (cFin==cIni-1)){//Se la mossa che sta facendo è mangiare un pezzo(muove in obliquo)
            if(a[rFin][cFin]!=0){ //Se nella cella in cui si sposta c'è un pezzo
                valido=true; //Allora la mossa è valida
            }
        }
    }else if((rFin==rIni-1) && (cFin==cIni)){ //Se è nero e se la mossa che sta facendo è andare avanti di una cella
        if(a[rFin][cFin]==0){ //Se nella cella in cui si sposta non c'è nulla
            valido=true; //Allora la mossa è valida
        }
        if((rIni==6) && (rFin==4) && (cFin==cIni)){ //Se la mossa che sta facendo è la prima , può andare avanti di due celle
            if(a[rFin][cFin]==0){ //Se nella cella in cui si sposta non c'è nulla
                valido=true; //Allora la mossa è valida
            }
        }
        
        if((rFin==rIni-1) && (cFin==cIni-1) || (cFin==cIni+1)){//Se la mossa che sta facendo è mangiare un pezzo(muove in obliquo)
            if(a[rFin][cFin]!=0){ //Se nella cella in cui si sposta c'è un pezzo
                valido=true; //Allora la mossa è valida
            }
        }
    }
    
    return valido;
}

*/





