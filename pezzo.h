class Pezzo{
    private:
    bool colore;    //true=bianco,false=nero
    bool stato;     //true=vivo, false=morto
    char nome;
    public:
    Pezzo(bool colore);
    void mossa();
    char getNome();
};