//
// Created by david on 06.05.2021.
//

#include "CCard.h"

CCard::CCard(const string &name, const string &description, const SEffect &effect) : name(name), desc(description), effect(effect){

}

const string &CCard::getName() const {
    return name;
}

const string &CCard::getDesc() const {
    return desc;
}

ostream &operator<<(ostream &os, CCard &src) {
    return src.printCard(os);
}

ostream &CCard::printCard(ostream &os) {
    return  os;
}

const int &CCard::getID() const {
    return effect.ID;
}

const SEffect &CCard::getEffect() const {
    return effect;
}





