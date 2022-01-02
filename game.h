using namespace std;
class Game{
    private:
    string modalita;
    bool randomColor();             //funzione privata per assegnare un colore casuale al giocatore
    public:
    Game(string mod);
    void start();                   //funzione fondamentale che contiene il ciclo del gioco
    bool sottoscacco();             //true se il re del giocatore che invoca la funzione è sottoscacco
    bool scaccomatto();             //true se il re del giocatore che invoca la funzione è in scaccomatto

};