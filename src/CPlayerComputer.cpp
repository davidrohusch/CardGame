#include "CPlayerComputer.h"


CPlayerComputer::CPlayerComputer(int hp, int mana, int gold, int attack) : CPlayer(hp, mana, gold, attack) {
}


string CPlayerComputer::whatAmI() const {
    return "PC";
}

void CPlayerComputer::goToDungeon(CGame *pGame) {

    srand(time(0));
    int goldgain = rand() % 10 + 1;
    int buffgain = rand() % 3 + 1;
    shared_ptr<CCard> randCard = pGame->randomCard();
    string dialog;

    int action = rand() % 3;
    switch(action){
        case(0):
            addCard( randCard);
            break;
        case(1):
            applyEffect(0,0,goldgain,0);
            ///random gold
            break;
        case(2):

            applyEffect(buffgain,buffgain,0,0);
            ///random buff
            break;
    }




}

void CPlayerComputer::playing(CGame *game) {
    mana+=2; //give player some mana
    int cnt = countPlayableCards();
    if(cnt==0) {cout << "Nepritel si lizl kartu" << endl; game->drawCard(hand); return;}
    if(cnt==1) {cout << "Nepritel zasel do dungeonu." << endl; goToDungeon(game); return; }

    int max = hand[0]->getEffect().cardValue;;
    int index = 0;
    for(unsigned int i = 0 ; i < hand.size() ; i++){
        if( hand[i]->canBePlayed(mana, gold) )
            if (hand[i]->getEffect().cardValue > max) {
                max = hand[i]->getEffect().cardValue;
                index = i;
            }
    }
    cout << "Nepritel zahral " << hand[index]->getName() << " a zpusobil tim: " << endl
    << "Narostly mu zivoty o " << to_string ( hand[index]->getEffect().hpSelf ) <<" bodu."
    << "Narostla mu sila o " << to_string ( hand[index]->getEffect().dmgSelf ) <<" bodu."
    << "Snizil ti zivoty o " <<to_string ( hand[index]->getEffect().hpEnemy )  <<" bodu."
    << "Snizil ti silu o " << to_string ( hand[index]->getEffect().dmgEnemy ) << " bodu.";

    playCard(index);
    hand.erase(hand.begin() + index);
    cout <<endl;

}

int CPlayerComputer::countPlayableCards() const{
    int cnt = 0;
    for(const auto &i : hand){
        if( i->canBePlayed(mana, gold) ) cnt++;
    }
    return cnt;
}

