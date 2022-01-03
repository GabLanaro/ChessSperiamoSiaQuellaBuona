#include <tuple>
class Player{
    private:
    bool colore;    //true=white,false=black
    bool tipo;      //true=umano,false=computer
    public:
    Player(bool colore,bool tipo);
    bool getColor() const;
    bool getTipo() const;
    void setTipo(bool tipo);
    std::tuple<int,int,int,int> mossa();
};
