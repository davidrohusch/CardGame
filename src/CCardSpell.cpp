//
// Created by david on 06.05.2021.
//

#include "CCardSpell.h"


CCardSpell::CCardSpell(const string &name, const string &desc, const SEffect &effect) : CCard(name, desc, effect) {

}



ostream &CCardSpell::printCard(ostream &os) {
    os << "\"" << name << "\"" << " " << 2 << " " << effect.price << " " << effect.hpSelf << " " << effect.dmgSelf << " "<< effect.hpEnemy << " "<< effect.dmgEnemy << " " << "\"" << desc << "\"" << endl ;
    return os;
}

bool CCardSpell::canBePlayed(int mana, int gold) const {
    return mana >= effect.price;
}

void CCardSpell::payPrice(int &mana, int &gold) {
    mana -= effect.price ;
}

