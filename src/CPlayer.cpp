#include "CPlayer.h"
#include <iostream>
#include <fstream>


bool CPlayer::dead () const{
    return hp <= 0;
}

CPlayer::CPlayer(int hp, int mana, int gold, int attack) :hp(hp), mana(mana), gold(gold), attack(attack) {
}

bool CPlayer::playCard(int cardNumber) {
    if ( ! hand[cardNumber]->canBePlayed(mana, gold) ) return false;

    hp += hand[cardNumber]->getEffect().hpSelf;
    attack += hand[cardNumber]->getEffect().dmgSelf;

    hand[cardNumber]->payPrice(mana, gold);

    shared_ptr<CPlayer> spFoo = enemyPlayer.lock();
    spFoo->applyEffect(hand[cardNumber]->getEffect().hpEnemy, hand[cardNumber]->getEffect().dmgEnemy , 0 , 0 );

    return true;
}


bool CPlayer::addCard(const shared_ptr<CCard> &card) {
    if(cardMax<hand.size()+1) return false;

    hand.push_back(card);
    return true;
}



void CPlayer::attackPlayer(const shared_ptr<CPlayer> &src, int dmg) {
    src->applyEffect(-dmg, 0 , 0 , 0);
}

void CPlayer::applyEffect(const int &hpself, const int &dmgself, const int &goldself, const int &manaself) {
    hp += hpself;
    attack += dmgself;
    gold += goldself;
    mana += manaself;
}



void CPlayer::setEnemy(shared_ptr<CPlayer> &enemy) {
    enemyPlayer = enemy;

}

bool CPlayer::save(const string &filename) {
    ofstream save;
    save.open(filename);
    if(save.is_open()){
        save << whatAmI()  << endl << hp << endl << mana << endl << gold << endl << attack << endl << cardMax   << endl;

        for(const auto &i : hand ){
            save << i->getID() << endl;
        }

    }else{
        save.close();
        throw "";
    }
    save.close();
    return true;
}

void CPlayer::setCardLimit(const int &n){
    cardMax=n;
}

int CPlayer::getHP() const {
    return hp;
}





