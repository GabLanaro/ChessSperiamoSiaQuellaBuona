#include "player.h"
Player::Player(bool color,bool tip){
    colore=color;
    tipo=tip;
}

bool Player::getColor(){
    return colore;
}

void Player::setTipo(bool tip){
    tipo=tip;
}