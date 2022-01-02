class Player{
    private:
    bool colore;    //true=white,false=black
    bool tipo;      //true=umano,false=computer
    public:
    Player(bool color,bool tip);
    bool getColor();
    void setTipo(bool tip);
};