#include "pezzo.h"

char Pezzo::getName() const{
    return name;
}

bool Pezzo::getColor() const{
    return color;
}

//*****PEDONE*****

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
    return true;
}

//*****TORRE*****

Torre::Torre(bool col){
    color=col;
    if(color==true){
        name='t';
    }
    else{
        name='T';
    }
    //funzione chooseName?
}

bool Torre::isValid(int ri, int ci, int rf, int cf){
    return true;
}

//*****CAVALLO*****

Cavallo::Cavallo(bool col){
    color=col;
    if(color==true){
        name='c';
    }
    else{
        name='C';
    }
    //funzione chooseName?
}

bool Cavallo::isValid(int ri, int ci, int rf, int cf){
    return true;
}

//*****ALFIERE*****

Alfiere::Alfiere(bool col){
    color=col;
    if(color==true){
        name='a';
    }
    else{
        name='A';
    }
    //funzione chooseName?
}

bool Alfiere::isValid(int ri, int ci, int rf, int cf){
    return true;
}

//*****RE*****

Re::Re(bool col){
    color=col;
    if(color==true){
        name='r';
    }
    else{
        name='R';
    }
    //funzione chooseName?
}

bool Re::isValid(int ri, int ci, int rf, int cf){
    return true;
}

//*****REGINA*****

Regina::Regina(bool col){
    color=col;
    if(color==true){
        name='d';
    }
    else{
        name='D';
    }
    //funzione chooseName?
}

bool Regina::isValid(int ri, int ci, int rf, int cf){
    return true;
}

/*

#include <iostream>
#include <string>

#define R 9
#define C 8

using namespace std;

bool isValid(int rIni, int cIni, int rFin, int cFin, bool valido, char nome,int a[R][C],int colorGio, int colorPez);

int main()
{
    int ri=1;
    int ci=0;
    int rf=2;
    int cf=0;
    bool valid=false;
    char name='P';
    string capo="\n";
    int arr[R][C];
    int colorGio=0; //colore dei pezzi del giocatore
    int colorPez=1; //colore del pezzo dell'avversario(quello che viene mangiato)
    
    
    for (int i = 0; i < 8; i++)
    {
            for (int j = 0; j < 8; j++)
        {
            arr[i][j] = 0;
        }
    }
    
    for (int i = 0; i < 8; i++){
        arr[8][i] = i;
    }
    
    arr[2][1]=1;
    
    for (int i = 0; i < 9; i++){
        cout << "r[" << i << "]";
        for (int j = 0; j < 8; j++){
            cout << arr[i][j];
        }
        cout << capo;
    } 
    
    cout << capo;
    cout << isValid(ri,ci,rf,cf,valid,name,arr,colorGio,colorPez);
    cout << capo;
    cout << valid;

    return 0;
}

//*******PEDONE*******(Bisogna invertire i check)

bool isValid(int rIni, int cIni, int rFin, int cFin, bool valido, char nome,int a[R][C],int colorGio, int colorPez){
    if(nome=='p'){ //Se è bianco
        if((rFin==rIni-1) && (cFin==cIni)){ //Se la mossa che sta facendo è andare avanti di una cella
            if(a[rFin][cFin]==0){ //Se nella cella in cui si sposta non c'è nulla
                valido=true; //Allora la mossa è valida
            }
        }
        
        if((rFin==rIni-2) && (cFin==cIni)){ //Se la mossa che sta facendo è la prima , può andare avanti di due celle
            if((a[rFin][cFin]==0) && (a[rFin-1][cFin]==0)){ //Se nella cella in cui si sposta non c'è nulla (e anche nel tragitto non c'è nulla)
                valido=true; //Allora la mossa è valida
            }
        }
        
        if((rFin==rIni-1) && (cFin==cIni+1) || (cFin==cIni-1)){//Se la mossa che sta facendo è mangiare un pezzo(muove in obliquo)
            if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella cella in cui si sposta c'è un pezzo e ha un colore diverso dal colore del giocatore
                valido=true; //Allora la mossa è valida
            }
        }
    }else if(nome=='P'){ //Se è nero
                if((rFin==rIni+1) && (cFin==cIni)){ //Se la mossa che sta facendo è andare avanti di una cella
                    if(a[rFin][cFin]==0){ //Se nella cella in cui si sposta non c'è nulla
                        valido=true; //Allora la mossa è valida
                  }
             }
        if((rFin==rIni+2) && (cFin==cIni)){ //Se la mossa che sta facendo è la prima , può andare avanti di due celle
            if((a[rFin][cFin]==0) && (a[rFin+1][cFin]==0)){ //Se nella cella in cui si sposta non c'è nulla
                valido=true; //Allora la mossa è valida
            }
        }
        
        if((rFin==rIni+1) && (cFin==cIni-1) || (cFin==cIni+1)){//Se la mossa che sta facendo è mangiare un pezzo(muove in obliquo)
            if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella cella in cui si sposta c'è un pezzo e ha un colore diverso dal colore del giocatore
                valido=true; //Allora la mossa è valida
            }
        }
    }
    
    return valido;
}

//*******TORRE*******

bool isValid(int rIni, int cIni, int rFin, int cFin, bool valido, char nome,int a[R][C], int colorGio, int colorPez){
    if(cIni==cFin){  //Se si sta spostando in verticale
        for(int i = rIni+1; i <= rFin; i++){  //Controllo ogni cella verso il basso
            if(i==rFin){  //Se l'indice arriva alla posizione finale
                if((a[rFin][cIni]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e ha il colore diverso da quello del giocatore
                    valido=true; //Allora la mossa è valida
                }
                else if(a[i][cIni]==0){ //Se nella posizione finale non c'è nulla
                    valido=true; //Allora la mossa è valida
                }
            }
            
            if(a[i][cIni]==0){ //Se le celle che incontra sono vuote
                valido=true; //Allora la mossa è valida
            }
        }
    }
    
    return valido;
}



*/





