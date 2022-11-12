//
// Created by david on 06.05.2021.
//

#include "CCardArtefakt.h"

CCardArtefakt::CCardArtefakt(const string &name, const string &desc, const SEffect &effect) : CCard(name, desc,
                                                                                                    effect) {

}



ostream &CCardArtefakt::printCard(ostream &os) {
    os << "\"" << name << "\"" << " " << 1 << " " << effect.price << " " << effect.hpSelf << " " << effect.dmgSelf << " "<< effect.hpEnemy << " "<< effect.dmgEnemy << " " << "\"" << desc << "\"" << endl ;
    return os;
}

bool CCardArtefakt::canBePlayed(int mana, int gold) const {
    return gold >= effect.price;
}

void CCardArtefakt::payPrice(int &mana, int &gold) {
    gold -= effect.price ;
}

