#include "pezzo.h"
#include "board.h"
#include "iostream"

char Pezzo::getName() const{
    return name;
}

bool Pezzo::getColor() const{
    return color;
}

Pezzo::~Pezzo(){ } //devo metterci un delete dentro? Oppure faccio il distruttore in board e faccio il delete del puntatore al pezzo?

//*****PEDONE****

Pedone::Pedone(bool c, char n){
    color=c;
    name=n;
}

bool Pedone::isValid(int rIni, int cIni, int rFin, int cFin, Board& b){
    Pezzo *PezzoIniziale = b.getPezzo(rIni,cIni); // Creo un puntatore al pezzo iniziale
    Pezzo *PezzoFinale = b.getPezzo(rFin,cFin); //Creo un puntatore al pezzo d'arrivo
    if(name=='p'){ //Se è bianco
        if((rFin==rIni+1) && (cFin==cIni) && (PezzoFinale==NULL)){ //Se la mossa che sta facendo è andare avanti di una cella e non c'è nessun pezzo
                return true; //Allora la mossa è valida
        }
        
        if((rFin==3) && (cFin==cIni) && (PezzoFinale==NULL) && (b.getPezzo(rIni+1,cFin)==NULL)){ //Se la mossa che sta facendo è la prima , può andare avanti di due celle e se nel tragitto e nella cella d'arrivo non ci sono pezzi
                return true; //Allora la mossa è valida
        }
        
        if((rFin==rIni+1) && ((cFin==cIni+1) || (cFin==cIni-1)) && (PezzoFinale!=NULL) && (PezzoFinale->getColor()!=PezzoIniziale->getColor())){ //Se nella cella in cui si sposta (muove in obliquo) c'è un pezzo e ha un colore diverso dal colore del giocatore
                return true; //Allora la mossa è valida
        }

    }else if(name=='P'){ //Se è nero
        if((rFin==rIni-1) && (cFin==cIni) && (PezzoFinale==NULL)){ //Se la mossa che sta facendo è andare avanti di una cella e non c'è nessun pezzo
                return true; //Allora la mossa è valida
        }
        
        if((rFin==4) && (cFin==cIni) && (PezzoFinale==NULL) && (b.getPezzo(rIni-1,cFin)==NULL)){ //Se la mossa che sta facendo è la prima , può andare avanti di due celle e se nel tragitto e nella cella d'arrivo non ci sono pezzi
                return true; //Allora la mossa è valida
        }
        
        if((rFin==rIni-1) && ((cFin==cIni-1) || (cFin==cIni+1)) && (PezzoFinale!=NULL) && (PezzoFinale->getColor()!=PezzoIniziale->getColor())){ //Se nella cella in cui si sposta (muove in obliquo) c'è un pezzo e ha un colore diverso dal colore del giocatore
                return true; //Allora la mossa è valida
        }
    }
    
    return false;
}

//*****TORRE*****

Torre::Torre(bool c, char n){
    color=c;
    name=n;
}

bool Torre::isValid(int rIni, int cIni, int rFin, int cFin, Board& b){
    Pezzo *PezzoIniziale = b.getPezzo(rIni,cIni); // Creo un puntatore al pezzo iniziale
    if(cIni==cFin){ //Se si sta spostando in verticale
        if(rIni>rFin){ //Se si sta spostando in basso
            for(int i = rIni-1; i >= rFin; i--){  //Controllo ogni cella verso il basso
                Pezzo *PezzoCorrente = b.getPezzo(i,cFin); //Creo un puntatore che segue il pezzo verso il basso
                if(i==rFin){  //Se l'indice arriva alla cella finale
                    if(((PezzoCorrente!=NULL) && (PezzoCorrente->getColor()!=PezzoIniziale->getColor())) || (PezzoCorrente==NULL)){ //Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; //Allora la mossa è valida
                    }
                }
                
                if(PezzoCorrente!=NULL){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
        }else if(rIni<rFin){ //Se si sta spostando verso l'alto
            for(int i = rIni+1; i <= rFin; i++){  //Controllo ogni cella verso l'alto
            Pezzo *PezzoCorrente = b.getPezzo(i,cFin); //Creo un puntatore che segue il pezzo verso l'alto
                if(i==rFin){  //Se l'indice arriva alla posizione finale
                    if(((PezzoCorrente!=NULL) && (PezzoCorrente->getColor()!=PezzoIniziale->getColor())) || (PezzoCorrente==NULL)){ //Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; //Allora la mossa è valida
                    }
                }
                
                if(PezzoCorrente!=NULL){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
        }
    }else if(rIni==rFin){ //Se si sta spostando in orizzontale
         if(cIni>cFin){ //Se si sta spostando verso sinistra
            for(int i = cIni-1; i >= cFin; i--){  //Controllo ogni cella verso sinistra
                Pezzo *PezzoCorrente = b.getPezzo(rFin,i); //Creo un puntatore che segue il pezzo verso sinistra
                if(i==cFin){  //Se l'indice arriva alla posizione finale
                    if(((PezzoCorrente!=NULL) && (PezzoCorrente->getColor()!=PezzoIniziale->getColor())) || (PezzoCorrente==NULL)){ //Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; //Allora la mossa è valida
                    }
                }
                
                if(PezzoCorrente!=NULL){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
        }else if(cIni<cFin){ //Se si sta spostando verso destra
            for(int i = cIni+1; i <= cFin; i++){  //Controllo ogni cella verso destra
                 Pezzo *PezzoCorrente = b.getPezzo(rFin,i); //Creo un puntatore che segue il pezzo verso destra
                if(i==cFin){  //Se l'indice arriva alla posizione finale
                    if(((PezzoCorrente!=NULL) && (PezzoCorrente->getColor()!=PezzoIniziale->getColor())) || (PezzoCorrente==NULL)){ //Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; //Allora la mossa è valida
                    }
                }
                
                if(PezzoCorrente!=NULL){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
        }
    }
    
    return false;
}

//*****CAVALLO*****

Cavallo::Cavallo(bool c, char n){
    color=c;
    name=n;
}

bool Cavallo::isValid(int rIni, int cIni, int rFin, int cFin, Board& b){
    Pezzo *PezzoIniziale = b.getPezzo(rIni,cIni); // Creo un puntatore al pezzo iniziale
    Pezzo *PezzoFinale = b.getPezzo(rFin,cFin); //Creo un puntatore alla cella d'arrivo
    if(((cFin==cIni+1) || (cFin==cIni-1)) && ((rFin==rIni+2) || (rFin==rIni-2))){ //Se si sposta di una colonna a destra o sinistra e di due righe in alto o in basso
        if(((PezzoFinale!=NULL) && (PezzoFinale->getColor()!=PezzoIniziale->getColor())) || (PezzoFinale==NULL)){ //Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
            return true; //Allora la mossa è valida
        }    
    }else if(((cFin==cIni+2) || (cFin==cIni-2)) && ((rFin==rIni+1) || (rFin==rIni-1))){ //Se si sposta di due colonne a destra o sinistra e di una riga in alto o in basso
            if(((PezzoFinale!=NULL) && (PezzoFinale->getColor()!=PezzoIniziale->getColor())) || (PezzoFinale==NULL)){ //Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                return true; //Allora la mossa è valida
            }    
    }
    return false;
}

//*****ALFIERE*****

Alfiere::Alfiere(bool c, char n){
    color=c;
    name=n;
}

bool Alfiere::isValid(int rIni, int cIni, int rFin, int cFin, Board& b){
    Pezzo *PezzoIniziale = b.getPezzo(rIni,cIni); // Creo un puntatore al pezzo iniziale
    int i,j; //indici i->riga, j->colonna
    if(cIni<cFin){ //Se ci si sta spostando verso destra
        if(rIni<rFin){ //Dal basso verso l'alto
            for(i=rIni+1,j=cIni+1;((i<=rFin) && (j<=cFin));i++,j++){//Per ogni cella che si attraversa
                Pezzo *PezzoCorrente = b.getPezzo(i,j); //Creo un puntatore che segue il pezzo verso l'alto in diagonale
                if((i==rFin) && (j==cFin)){  //Se l'indice arriva alla posizione finale
                    if(((PezzoCorrente!=NULL) && (PezzoCorrente->getColor()!=PezzoIniziale->getColor())) || (PezzoCorrente==NULL)){ //Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; //Allora la mossa è valida
                    }
                }

                if(PezzoCorrente!=NULL){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
            
        }else if(rIni>rFin){ //Dall'alto verso il basso
            for(i=rIni-1,j=cIni+1;((i>=rFin) && (j<=cFin));i--,j++){//Per ogni cella che si attraversa
                Pezzo *PezzoCorrente = b.getPezzo(i,j); //Creo un puntatore che segue il pezzo verso il basso in diagonale
                if((i==rFin) && (j==cFin)){  //Se l'indice arriva alla posizione finale
                    if(((PezzoCorrente!=NULL) && (PezzoCorrente->getColor()!=PezzoIniziale->getColor())) || (PezzoCorrente==NULL)){ //Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; //Allora la mossa è valida
                    }
                }
                
                if(PezzoCorrente!=NULL){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
        }
    }else if(cIni>cFin){ //Se si sta spostando verso sinistra
        if(rIni<rFin){ //Dal basso verso l'alto
           for(i=rIni+1,j=cIni-1;((i<=rFin) && (j>=cFin));i++,j--){//Per ogni cella che si attraversa
                Pezzo *PezzoCorrente = b.getPezzo(i,j); //Creo un puntatore che segue il pezzo verso l'alto in diagonale
                if((i==rFin) && (j==cFin)){  //Se l'indice arriva alla posizione finale
                    if(((PezzoCorrente!=NULL) && (PezzoCorrente->getColor()!=PezzoIniziale->getColor())) || (PezzoCorrente==NULL)){ //Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; //Allora la mossa è valida
                    }
                }
                
                if(PezzoCorrente!=NULL){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
            
        }else if(rIni>rFin){ //Dall'alto verso il basso
           for(i=rIni-1,j=cIni-1;((i>=rFin) && (j>=cFin));i--,j--){//Per ogni cella che si attraversa
                Pezzo *PezzoCorrente = b.getPezzo(i,j); //Creo un puntatore che segue il pezzo verso il basso in diagonale
                if((i==rFin) && (j==cFin)){  //Se l'indice arriva alla posizione finale
                    if(((PezzoCorrente!=NULL) && (PezzoCorrente->getColor()!=PezzoIniziale->getColor())) || (PezzoCorrente==NULL)){ //Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; //Allora la mossa è valida
                    }
                }
                
                if(PezzoCorrente!=NULL){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
        }
    }
    
    return false;
}

//*****REGINA*****

Regina::Regina(bool c, char n){
    color=c;
    name=n;
}

bool Regina::isValid(int rIni, int cIni, int rFin, int cFin, Board& b){ //Data dai movimenti di Alfiere + Torre
    Pezzo *PezzoIniziale = b.getPezzo(rIni,cIni); // Creo un puntatore al pezzo iniziale
    //Controlli in obliquo (Alfiere)
    int i,j; //indici i->riga, j->colonna
    if(cIni<cFin){ //Se ci si sta spostando verso destra
        if(rIni<rFin){ //Dal basso verso l'alto
            for(i=rIni+1,j=cIni+1;((i<=rFin) && (j<=cFin));i++,j++){//Per ogni cella che si attraversa
                Pezzo *PezzoCorrente = b.getPezzo(i,j); //Creo un puntatore che segue il pezzo verso l'alto in diagonale
                if((i==rFin) && (j==cFin)){  //Se l'indice arriva alla posizione finale
                    if(((PezzoCorrente!=NULL) && (PezzoCorrente->getColor()!=PezzoIniziale->getColor())) || (PezzoCorrente==NULL)){ //Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; //Allora la mossa è valida
                    }
                }

                if(PezzoCorrente!=NULL){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
            
        }else if(rIni>rFin){ //Dall'alto verso il basso
            for(i=rIni-1,j=cIni+1;((i>=rFin) && (j<=cFin));i--,j++){//Per ogni cella che si attraversa
                Pezzo *PezzoCorrente = b.getPezzo(i,j); //Creo un puntatore che segue il pezzo verso il basso in diagonale
                if((i==rFin) && (j==cFin)){  //Se l'indice arriva alla posizione finale
                    if(((PezzoCorrente!=NULL) && (PezzoCorrente->getColor()!=PezzoIniziale->getColor())) || (PezzoCorrente==NULL)){ //Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; //Allora la mossa è valida
                    }
                }
                
                if(PezzoCorrente!=NULL){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
        }
    }else if(cIni>cFin){ //Se si sta spostando verso sinistra
        if(rIni<rFin){ //Dal basso verso l'alto
           for(i=rIni+1,j=cIni-1;((i<=rFin) && (j>=cFin));i++,j--){//Per ogni cella che si attraversa
                Pezzo *PezzoCorrente = b.getPezzo(i,j); //Creo un puntatore che segue il pezzo verso l'alto in diagonale
                if((i==rFin) && (j==cFin)){  //Se l'indice arriva alla posizione finale
                    if(((PezzoCorrente!=NULL) && (PezzoCorrente->getColor()!=PezzoIniziale->getColor())) || (PezzoCorrente==NULL)){ //Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; //Allora la mossa è valida
                    }
                }
                
                if(PezzoCorrente!=NULL){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
            
        }else if(rIni>rFin){ //Dall'alto verso il basso
           for(i=rIni-1,j=cIni-1;((i>=rFin) && (j>=cFin));i--,j--){//Per ogni cella che si attraversa
                Pezzo *PezzoCorrente = b.getPezzo(i,j); //Creo un puntatore che segue il pezzo verso il basso in diagonale
                if((i==rFin) && (j==cFin)){  //Se l'indice arriva alla posizione finale
                    if(((PezzoCorrente!=NULL) && (PezzoCorrente->getColor()!=PezzoIniziale->getColor())) || (PezzoCorrente==NULL)){ //Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; //Allora la mossa è valida
                    }
                }
                
                if(PezzoCorrente!=NULL){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
        }
    }
    
    //Controlli in verticale e orizzontale (Torre)
    if(cIni==cFin){ //Se si sta spostando in verticale
        if(rIni>rFin){ //Se si sta spostando in basso
            for(int i = rIni-1; i >= rFin; i--){  //Controllo ogni cella verso il basso
                Pezzo *PezzoCorrente = b.getPezzo(i,cFin); //Creo un puntatore che segue il pezzo verso il basso
                if(i==rFin){  //Se l'indice arriva alla cella finale
                    if(((PezzoCorrente!=NULL) && (PezzoCorrente->getColor()!=PezzoIniziale->getColor())) || (PezzoCorrente==NULL)){ //Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; //Allora la mossa è valida
                    }
                }
                
                if(PezzoCorrente!=NULL){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
        }else if(rIni<rFin){ //Se si sta spostando verso l'alto
            for(int i = rIni+1; i <= rFin; i++){  //Controllo ogni cella verso l'alto
            Pezzo *PezzoCorrente = b.getPezzo(i,cFin); //Creo un puntatore che segue il pezzo verso l'alto
                if(i==rFin){  //Se l'indice arriva alla posizione finale
                    if(((PezzoCorrente!=NULL) && (PezzoCorrente->getColor()!=PezzoIniziale->getColor())) || (PezzoCorrente==NULL)){ //Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; //Allora la mossa è valida
                    }
                }
                
                if(PezzoCorrente!=NULL){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
        }
    }else if(rIni==rFin){ //Se si sta spostando in orizzontale
         if(cIni>cFin){ //Se si sta spostando verso sinistra
            for(int i = cIni-1; i >= cFin; i--){  //Controllo ogni cella verso sinistra
                Pezzo *PezzoCorrente = b.getPezzo(rFin,i); //Creo un puntatore che segue il pezzo verso sinistra
                if(i==cFin){  //Se l'indice arriva alla posizione finale
                    if(((PezzoCorrente!=NULL) && (PezzoCorrente->getColor()!=PezzoIniziale->getColor())) || (PezzoCorrente==NULL)){ //Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; //Allora la mossa è valida
                    }
                }
                
                if(PezzoCorrente!=NULL){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
        }else if(cIni<cFin){ //Se si sta spostando verso destra
            for(int i = cIni+1; i <= cFin; i++){  //Controllo ogni cella verso destra
                 Pezzo *PezzoCorrente = b.getPezzo(rFin,i); //Creo un puntatore che segue il pezzo verso destra
                if(i==cFin){  //Se l'indice arriva alla posizione finale
                    if(((PezzoCorrente!=NULL) && (PezzoCorrente->getColor()!=PezzoIniziale->getColor())) || (PezzoCorrente==NULL)){ //Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
                        return true; //Allora la mossa è valida
                    }
                }
                
                if(PezzoCorrente!=NULL){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
        }
    }
    
    return false;
}

//*****RE*****

Re::Re(bool c, char n){
    color=c;
    name=n;
}

bool Re::isValid(int rIni, int cIni, int rFin, int cFin, Board& b){
    Pezzo *PezzoIniziale = b.getPezzo(rIni,cIni); // Creo un puntatore al pezzo iniziale
    Pezzo *PezzoFinale = b.getPezzo(rFin,cFin); //Creo un puntatore alla cella d'arrivo
    if(((rFin==rIni+1) || (rFin==rIni-1)  || (rFin==rIni)) && ((cFin==cIni+1) || (cFin==cIni-1) || (cFin==cIni))){ //Se si sta spostando di una cella in qualsiasi direzione
        if(((PezzoFinale!=NULL) && (PezzoFinale->getColor()!=PezzoIniziale->getColor())) || (PezzoFinale==NULL)){ //Se nella cella finale c'è un pezzo e ha il colore diverso da quello del giocatore oppure se nella cella finale non c'è nessun pezzo
            return true; //Allora la mossa è valida
        }
    }
    return false;
}


/*

#include <iostream>
#include <string>

#define R 9
#define C 8

using namespace std;

bool isValid(int rIni, int cIni, int rFin, int cFin, (char nome)->(color),int a[R][C],(int colorGio), (int colorPez);

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

//*******PEDONE*******

bool isValid(int rIni, int cIni, int rFin, int cFin, bool valido, char nome,int a[R][C],int colorGio, int colorPez){
    if(nome=='p'){ //Se è bianco
        if((rFin==rIni+1) && (cFin==cIni)){ //Se la mossa che sta facendo è andare avanti di una cella
            if(a[rFin][cFin]==0){ //Se nella cella in cui si sposta non c'è nulla
                valido=true; //Allora la mossa è valida
            }
        }
        
        if((rFin==3) && (cFin==cIni)){ //Se la mossa che sta facendo è la prima , può andare avanti di due celle
            if((a[rFin][cFin]==0) && (a[rFin+1][cFin]==0)){ //Se nella cella in cui si sposta non c'è nulla (e anche nel tragitto non c'è nulla)
                valido=true; //Allora la mossa è valida
            }
        }
        
        if((rFin==rIni+1) && (cFin==cIni+1) || (cFin==cIni-1)){//Se la mossa che sta facendo è mangiare un pezzo(muove in obliquo)
            if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella cella in cui si sposta c'è un pezzo e ha un colore diverso dal colore del giocatore
                valido=true; //Allora la mossa è valida
            }
        }
    }else if(nome=='P'){ //Se è nero
                if((rFin==rIni-1) && (cFin==cIni)){ //Se la mossa che sta facendo è andare avanti di una cella
                    if(a[rFin][cFin]==0){ //Se nella cella in cui si sposta non c'è nulla
                        valido=true; //Allora la mossa è valida
                  }
             }
        if((rFin==4) && (cFin==cIni)){ //Se la mossa che sta facendo è la prima , può andare avanti di due celle
            if((a[rFin][cFin]==0) && (a[rFin+1][cFin]==0)){ //Se nella cella in cui si sposta non c'è nulla
                valido=true; //Allora la mossa è valida
            }
        }
        
        if((rFin==rIni-1) && (cFin==cIni-1) || (cFin==cIni+1)){//Se la mossa che sta facendo è mangiare un pezzo(muove in obliquo)
            if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella cella in cui si sposta c'è un pezzo e ha un colore diverso dal colore del giocatore
                valido=true; //Allora la mossa è valida
            }
        }
    }
    
    return valido;
}

//*******TORRE*******

bool isValid(int rIni, int cIni, int rFin, int cFin, bool valido, char nome,int a[R][C], int colorGio, int colorPez){
    if(cIni==cFin){ //Se si sta spostando in verticale
        if(rIni>rFin){ //Se si sta spostando in basso
            for(int i = rIni-1; i >= rFin; i--){  //Controllo ogni cella verso il basso
                if(i==rFin){  //Se l'indice arriva alla posizione finale
                    if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e ha il colore diverso da quello del giocatore
                        return true; //Allora la mossa è valida
                    }
                    else if(a[rFin][cFin]==0){ //Se nella posizione finale non c'è nulla
                        valido=true; //Allora la mossa è valida
                        //Forse con il return risparmio tempo?
                        //Posso unirlo all'if di prima?
                    }
                }
                
                if(a[i][cIni]!=0){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
        }else if(rIni<rFin){ //Se si sta spostando verso l'alto
            for(int i = rIni+1; i <= rFin; i++){  //Controllo ogni cella verso l'alto
                if(i==rFin){  //Se l'indice arriva alla posizione finale
                    if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e ha il colore diverso da quello del giocatore
                        return true; //Allora la mossa è valida
                    }
                    else if(a[rFin][cFin]==0){ //Se nella posizione finale non c'è nulla
                        valido=true; //Allora la mossa è valida
                        //Forse con il return risparmio tempo?
                        //Posso unirlo all'if di prima?
                    }
                }
                
                if(a[i][cIni]!=0){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
        }
    }else if(rIni==rFin){ //Se si sta spostando in orizzontale
         if(cIni>cFin){ //Se si sta spostando verso sinistra
            for(int i = cIni-1; i >= cFin; i--){  //Controllo ogni cella verso sinistra
                if(i==cFin){  //Se l'indice arriva alla posizione finale
                    if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e ha il colore diverso da quello del giocatore
                        return true; //Allora la mossa è valida
                    }
                    else if(a[rFin][cFin]==0){ //Se nella posizione finale non c'è nulla
                        valido=true; //Allora la mossa è valida
                        //Forse con il return risparmio tempo?
                        //Posso unirlo all'if di prima?
                    }
                }
                
                if(a[rIni][i]!=0){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
        }else if(cIni<cFin){ //Se si sta spostando verso destra
            for(int i = cIni+1; i <= cFin; i++){  //Controllo ogni cella verso destra
                if(i==cFin){  //Se l'indice arriva alla posizione finale
                    if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e ha il colore diverso da quello del giocatore
                        return true; //Allora la mossa è valida
                    }
                    else if(a[rFin][cFin]==0){ //Se nella posizione finale non c'è nulla
                        valido=true; //Allora la mossa è valida
                        //Forse con il return risparmio tempo?
                        //Posso unirlo all'if di prima?
                    }
                }
                
                if(a[rIni][i]!=0){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
        }
    }
    
    return valido;
}

//*******CAVALLO*******

bool isValid(int rIni, int cIni, int rFin, int cFin, bool valido, char nome,int a[R][C], int colorGio, int colorPez){
    if((cFin==cIni+1) || (cFin==cIni-1)){ //Se si sposta di una colonna a destra o sinistra
        if((rFin==rIni+2) || (rFin==rIni-2)){ //Se si sposta di due righe in alto o in basso (Posso metterlo insieme all'if di prima?)
            if(a[rFin][cFin]==0){ //Se la posizione finale è vuota
                valido=true; //Allora la mossa è valida
            }else if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e il colore del pezzo è diverso da quello del giocatore
                valido=true; //Allora la mossa è valida
            }
        }
        
    }else if((cFin==cIni+2) || (cFin==cIni-2)){ //Se si sposta di due colonne a destra o sinistra
        if((rFin==rIni+1) || (rFin==rIni-1)){ //Se si sposta di una riga in alto o in basso (Posso metterlo insieme all'if di prima?)
            if(a[rFin][cFin]==0){ //Se la posizione finale è vuota
                valido=true; //Allora la mossa è valida
            }else if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e il colore del pezzo è diverso da quello del giocatore
                valido=true; //Allora la mossa è valida
            }
        }
    }
    
    return valido;
}

//*****ALFIERE*****

bool isValid(int rIni, int cIni, int rFin, int cFin, bool valido, char nome,int a[R][C], int colorGio, int colorPez){
    int i,j; //indici i->riga, j->colonna
    if(cIni<cFin){ //Se ci si sta spostando verso destra
        if(rIni<rFin){ //Dal basso verso l'alto
            for(i=rIni+1,j=cIni+1;((i<=rFin) && (j<=cFin));i++,j++){//Per ogni cella che si attraversa
                if((i==rFin) && (j==cFin)){  //Se l'indice arriva alla posizione finale
                    if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e ha il colore diverso da quello del giocatore
                        return true; //Allora la mossa è valida
                    }
                    else if(a[rFin][cFin]==0){ //Se nella posizione finale non c'è nulla
                        valido=true; //Allora la mossa è valida
                        //Forse con il return risparmio tempo?
                        //Posso unirlo all'if di prima?
                    }
                }
                
                if(a[i][j]!=0){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
            
        }else if(rIni>rFin){ //Dall'alto verso il basso
            for(i=rIni-1,j=cIni+1;((i>=rFin) && (j<=cFin));i--,j++){//Per ogni cella che si attraversa
                if((i==rFin) && (j==cFin)){  //Se l'indice arriva alla posizione finale
                    if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e ha il colore diverso da quello del giocatore
                        return true; //Allora la mossa è valida
                    }
                    else if(a[rFin][cFin]==0){ //Se nella posizione finale non c'è nulla
                        valido=true; //Allora la mossa è valida
                        //Forse con il return risparmio tempo?
                        //Posso unirlo all'if di prima?
                    }
                }
                
                if(a[i][j]!=0){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
        }
    }else if(cIni>cFin){ //Se si sta spostando verso sinistra
        if(rIni<rFin){ //Dal basso verso l'alto
           for(i=rIni+1,j=cIni-1;((i<=rFin) && (j>=cFin));i++,j--){//Per ogni cella che si attraversa
                 if((i==rFin) && (j==cFin)){  //Se l'indice arriva alla posizione finale
                    if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e ha il colore diverso da quello del giocatore
                        return true; //Allora la mossa è valida
                    }
                    else if(a[rFin][cFin]==0){ //Se nella posizione finale non c'è nulla
                        valido=true; //Allora la mossa è valida
                        //Forse con il return risparmio tempo?
                        //Posso unirlo all'if di prima?
                    }
                }
                
                if(a[i][j]!=0){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
            
        }else if(rIni>rFin){ //Dall'alto verso il basso
           for(i=rIni-1,j=cIni-1;((i>=rFin) && (j>=cFin));i--,j--){//Per ogni cella che si attraversa
                if((i==rFin) && (j==cFin)){  //Se l'indice arriva alla posizione finale
                    if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e ha il colore diverso da quello del giocatore
                        return true; //Allora la mossa è valida
                    }
                    else if(a[rFin][cFin]==0){ //Se nella posizione finale non c'è nulla
                        valido=true; //Allora la mossa è valida
                        //Forse con il return risparmio tempo?
                        //Posso unirlo all'if di prima?
                    }
                }
                
                if(a[i][j]!=0){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
        }
    }
    
    return valido;
}


//*****REGINA*****

bool isValid(int rIni, int cIni, int rFin, int cFin, bool valido, char nome,int a[R][C], int colorGio, int colorPez){
    //Controlli in obliquo
    int i,j; //indici i->riga, j->colonna
    if(cIni<cFin){ //Se ci si sta spostando verso destra
        if(rIni<rFin){ //Dal basso verso l'alto
            for(i=rIni+1,j=cIni+1;((i<=rFin) && (j<=cFin));i++,j++){//Per ogni cella che si attraversa
                if((i==rFin) && (j==cFin)){  //Se l'indice arriva alla posizione finale
                    if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e ha il colore diverso da quello del giocatore
                        return true; //Allora la mossa è valida
                    }
                    else if(a[rFin][cFin]==0){ //Se nella posizione finale non c'è nulla
                        valido=true; //Allora la mossa è valida
                        //Forse con il return risparmio tempo?
                        //Posso unirlo all'if di prima?
                    }
                }
                
                if(a[i][j]!=0){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
            
        }else if(rIni>rFin){ //Dall'alto verso il basso
            for(i=rIni-1,j=cIni+1;((i>=rFin) && (j<=cFin));i--,j++){//Per ogni cella che si attraversa
                if((i==rFin) && (j==cFin)){  //Se l'indice arriva alla posizione finale
                    if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e ha il colore diverso da quello del giocatore
                        return true; //Allora la mossa è valida
                    }
                    else if(a[rFin][cFin]==0){ //Se nella posizione finale non c'è nulla
                        valido=true; //Allora la mossa è valida
                        //Forse con il return risparmio tempo?
                        //Posso unirlo all'if di prima?
                    }
                }
                
                if(a[i][j]!=0){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
        }
    }else if(cIni>cFin){ //Se si sta spostando verso sinistra
        if(rIni<rFin){ //Dal basso verso l'alto
           for(i=rIni+1,j=cIni-1;((i<=rFin) && (j>=cFin));i++,j--){//Per ogni cella che si attraversa
                 if((i==rFin) && (j==cFin)){  //Se l'indice arriva alla posizione finale
                    if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e ha il colore diverso da quello del giocatore
                        return true; //Allora la mossa è valida
                    }
                    else if(a[rFin][cFin]==0){ //Se nella posizione finale non c'è nulla
                        valido=true; //Allora la mossa è valida
                        //Forse con il return risparmio tempo?
                        //Posso unirlo all'if di prima?
                    }
                }
                
                if(a[i][j]!=0){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
            
        }else if(rIni>rFin){ //Dall'alto verso il basso
           for(i=rIni-1,j=cIni-1;((i>=rFin) && (j>=cFin));i--,j--){//Per ogni cella che si attraversa
                if((i==rFin) && (j==cFin)){  //Se l'indice arriva alla posizione finale
                    if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e ha il colore diverso da quello del giocatore
                        return true; //Allora la mossa è valida
                    }
                    else if(a[rFin][cFin]==0){ //Se nella posizione finale non c'è nulla
                        valido=true; //Allora la mossa è valida
                        //Forse con il return risparmio tempo?
                        //Posso unirlo all'if di prima?
                    }
                }
                
                if(a[i][j]!=0){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
        }
    }
    
    //Controlli in verticale e orizzontale
    if(cIni==cFin){ //Se si sta spostando in verticale
        if(rIni>rFin){ //Se si sta spostando in basso
            for(int i = rIni-1; i >= rFin; i--){  //Controllo ogni cella verso il basso
                if(i==rFin){  //Se l'indice arriva alla posizione finale
                    if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e ha il colore diverso da quello del giocatore
                        return true; //Allora la mossa è valida
                    }
                    else if(a[rFin][cFin]==0){ //Se nella posizione finale non c'è nulla
                        valido=true; //Allora la mossa è valida
                        //Forse con il return risparmio tempo?
                        //Posso unirlo all'if di prima?
                    }
                }
                
                if(a[i][cIni]!=0){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
        }else if(rIni<rFin){ //Se si sta spostando verso l'alto
            for(int i = rIni+1; i <= rFin; i++){  //Controllo ogni cella verso l'alto
                if(i==rFin){  //Se l'indice arriva alla posizione finale
                    if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e ha il colore diverso da quello del giocatore
                        return true; //Allora la mossa è valida
                    }
                    else if(a[rFin][cFin]==0){ //Se nella posizione finale non c'è nulla
                        valido=true; //Allora la mossa è valida
                        //Forse con il return risparmio tempo?
                        //Posso unirlo all'if di prima?
                    }
                }
                
                if(a[i][cIni]!=0){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
        }
    }else if(rIni==rFin){ //Se si sta spostando in orizzontale
         if(cIni>cFin){ //Se si sta spostando verso sinistra
            for(int i = cIni-1; i >= cFin; i--){  //Controllo ogni cella verso sinistra
                if(i==cFin){  //Se l'indice arriva alla posizione finale
                    if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e ha il colore diverso da quello del giocatore
                        return true; //Allora la mossa è valida
                    }
                    else if(a[rFin][cFin]==0){ //Se nella posizione finale non c'è nulla
                        valido=true; //Allora la mossa è valida
                        //Forse con il return risparmio tempo?
                        //Posso unirlo all'if di prima?
                    }
                }
                
                if(a[rIni][i]!=0){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
        }else if(cIni<cFin){ //Se si sta spostando verso destra
            for(int i = cIni+1; i <= cFin; i++){  //Controllo ogni cella verso destra
                if(i==cFin){  //Se l'indice arriva alla posizione finale
                    if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e ha il colore diverso da quello del giocatore
                        return true; //Allora la mossa è valida
                    }
                    else if(a[rFin][cFin]==0){ //Se nella posizione finale non c'è nulla
                        valido=true; //Allora la mossa è valida
                        //Forse con il return risparmio tempo?
                        //Posso unirlo all'if di prima?
                    }
                }
                
                if(a[rIni][i]!=0){ //Se le celle che incontra presentano un pezzo
                    return false; //Allora la mossa non è valida
                }
            }
        }
    }
    
    return valido;
}

//*****RE*****

bool isValid(int rIni, int cIni, int rFin, int cFin, bool valido, char nome,int a[R][C], int colorGio, int colorPez){
    //Controlli in obliquo
    int i,j; //indici i->riga, j->colonna
    if(cIni<cFin){ //Se ci si sta spostando verso destra
        if(rIni<rFin){ //Dal basso verso l'alto
            if((rFin==rIni+1) && (cFin==cIni+1)){ //Se si sta spostando di una cella
                if(a[rFin][cFin]==0){ //Se nella posizione finale non c'è nulla
                    valido=true; //Allora la mossa è valida
                    //Forse con il return risparmio tempo
                }else if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e ha il colore diverso da quello del giocatore
                    valido=true; //Allora la mossa è valida
                    //Forse con il return risparmio tempo
                }
            }
            
        }else if(rIni>rFin){ //Dall'alto verso il basso
            if((rFin==rIni-1) && (cFin==cIni+1)){ //Se si sta spostando di una cella
                if(a[rFin][cFin]==0){ //Se nella posizione finale non c'è nulla
                    valido=true; //Allora la mossa è valida
                    //Forse con il return risparmio tempo
                }else if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e ha il colore diverso da quello del giocatore
                    valido=true; //Allora la mossa è valida
                    //Forse con il return risparmio tempo
                }
            }
        }
    }else if(cIni>cFin){ //Se si sta spostando verso sinistra
        if(rIni<rFin){ //Dal basso verso l'alto
           if((rFin==rIni+1) && (cFin==cIni-1)){ //Se si sta spostando di una cella
                if(a[rFin][cFin]==0){ //Se nella posizione finale non c'è nulla
                    valido=true; //Allora la mossa è valida
                    //Forse con il return risparmio tempo
                }else if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e ha il colore diverso da quello del giocatore
                    valido=true; //Allora la mossa è valida
                    //Forse con il return risparmio tempo
                }
            }
        }else if(rIni>rFin){ //Dall'alto verso il basso
           if((rFin==rIni-1) && (cFin==cIni-1)){ //Se si sta spostando di una cella
                if(a[rFin][cFin]==0){ //Se nella posizione finale non c'è nulla
                    valido=true; //Allora la mossa è valida
                    //Forse con il return risparmio tempo
                }else if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e ha il colore diverso da quello del giocatore
                    valido=true; //Allora la mossa è valida
                    //Forse con il return risparmio tempo
                }
            }
        }
    }
    
    //Controlli in verticale e orizzontale
    if(cIni==cFin){ //Se si sta spostando in verticale
        if(rIni>rFin){ //Se si sta spostando in basso
            if((rFin==rIni-1) && (cFin==cIni)){ //Se si sta spostando di una cella
                if(a[rFin][cFin]==0){ //Se nella posizione finale non c'è nulla
                    valido=true; //Allora la mossa è valida
                    //Forse con il return risparmio tempo
                }else if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e ha il colore diverso da quello del giocatore
                    valido=true; //Allora la mossa è valida
                    //Forse con il return risparmio tempo
                }
            }
        }else if(rIni<rFin){ //Se si sta spostando verso l'alto
            if((rFin==rIni+1) && (cFin==cIni)){ //Se si sta spostando di una cella
                if(a[rFin][cFin]==0){ //Se nella posizione finale non c'è nulla
                    valido=true; //Allora la mossa è valida
                    //Forse con il return risparmio tempo
                }else if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e ha il colore diverso da quello del giocatore
                    valido=true; //Allora la mossa è valida
                    //Forse con il return risparmio tempo
                }
            }
        }
    }else if(rIni==rFin){ //Se si sta spostando in orizzontale
         if(cIni>cFin){ //Se si sta spostando verso sinistra
            if((rFin==rIni) && (cFin==cIni-1)){ //Se si sta spostando di una cella
                if(a[rFin][cFin]==0){ //Se nella posizione finale non c'è nulla
                    valido=true; //Allora la mossa è valida
                    //Forse con il return risparmio tempo
                }else if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e ha il colore diverso da quello del giocatore
                    valido=true; //Allora la mossa è valida
                    //Forse con il return risparmio tempo
                }
            }
        }else if(cIni<cFin){ //Se si sta spostando verso destra
           if((rFin==rIni) && (cFin==cIni+1)){ //Se si sta spostando di una cella
                if(a[rFin][cFin]==0){ //Se nella posizione finale non c'è nulla
                    valido=true; //Allora la mossa è valida
                    //Forse con il return risparmio tempo
                }else if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e ha il colore diverso da quello del giocatore
                    valido=true; //Allora la mossa è valida
                    //Forse con il return risparmio tempo
                }
            }
        }
    }
    
    return valido;
}

//*****RE(ALTERNATIVO)*****

bool isValid(int rIni, int cIni, int rFin, int cFin, bool valido, char nome,int a[R][C], int colorGio, int colorPez){
    if(((rFin==rIni+1) || (rFin==rIni-1)  || (rFin==rIni)) && ((cFin==cIni+1) || (cFin==cIni-1) || (cFin==cIni))){ //Se si sta spostando di una cella
        if(a[rFin][cFin]==0){ //Se nella posizione finale non c'è nulla
                    valido=true; //Allora la mossa è valida
                    //Forse con il return risparmio tempo
                }else if((a[rFin][cFin]!=0) && (colorGio!=colorPez)){ //Se nella posizione finale c'è un pezzo e ha il colore diverso da quello del giocatore
                    valido=true; //Allora la mossa è valida
                    //Forse con il return risparmio tempo
                }    
    }
    return valido;
}

*/
