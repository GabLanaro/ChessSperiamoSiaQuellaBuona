class Pezzo{
    private:
    bool colore;    //true=bianco,false=nero
    bool stato;     //true=vivo, false=morto
    public:
    Pezzo(bool colore);
    void mossa();
};