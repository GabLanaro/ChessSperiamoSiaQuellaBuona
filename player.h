class Player{
    private:
    bool colore;    //true=white,false=black
    bool tipo;      //true=umano,false=computer
    public:
    Player(bool colore,bool tipo);
    bool getColor() const;
    void setTipo(bool tipo);
    void mossa();
};
