#include "player.h"
Player::Player(bool colore,bool tipo){
    this->colore=colore;
    this->tipo=tipo;
}

bool Player::getColor() const{
    return colore;
}

void Player::setTipo(bool tipo){
    this->tipo=tipo;
}

void Player::mossa(){
    if(this->tipo==true){
        
    }
}