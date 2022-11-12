#include "CPlayerComputer.h"


CPlayerComputer::CPlayerComputer(int hp, int mana, int gold, int attack) : CPlayer(hp, mana, gold, attack) {
}


string CPlayerComputer::whatAmI() const {
    return "PC";
}

void CPlayerComputer::goToDungeon(WINDOW *w, CGame *pGame) {

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

void CPlayerComputer::playing(CGame *pGame) {
    mana += 2; //give player some mana
    int cnt = countPlayableCards();
    if (cnt == 1) {
        printw("enemy drew a card");
        refresh();
        getch();
        pGame->drawCard(hand);
        return;
    }
    if (cnt == 0) {
        printw("Enemy went to a dungeon");
        refresh();
        getch();
        goToDungeon(nullptr, pGame);
        return;
    }

    int max = hand[0]->getEffect().cardValue;;
    int index = -1;


    if (hp < 20)
        for (unsigned int i = 0; i < hand.size(); i++) {
            if (hand[i]->canBePlayed(mana, gold))
                if (hand[i]->getEffect().cardValue > max) {
                    max = hand[i]->getEffect().cardValue;
                    index = i;
                }
        }
    if (index == -1)
        for (unsigned int i = 0; i < hand.size(); i++) {
            if (hand[i]->canBePlayed(mana, gold))
                if (hand[i]->getEffect().hpSelf > max) {
                    max = hand[i]->getEffect().hpSelf;
                    index = i;
                }
        }
    if (index == -1) index = 0;

    string text = "Enemy played " + hand[index]->getName() + " And it did:\n";
    if (hand[index]->getEffect().hpSelf != 0)
        text += "His life increased by " + to_string(hand[index]->getEffect().hpSelf) + "\n";
    if (hand[index]->getEffect().dmgSelf != 0)
        text += "His damage power increased by " + to_string(hand[index]->getEffect().dmgSelf) + "\n";
    if (hand[index]->getEffect().hpEnemy != 0)
        text += "Your life decreased by " + to_string(hand[index]->getEffect().hpEnemy) + "\n";
    if (hand[index]->getEffect().dmgEnemy != 0)
        text += "Your damage power decreased by " + to_string(hand[index]->getEffect().dmgEnemy) + "\n";

    printw(text.c_str());
    refresh();
    getch();


    playCard(index);
    hand.erase(hand.begin() + index);

}

int CPlayerComputer::countPlayableCards() const{
    int cnt = 0;
    for(const auto &i : hand){
        if( i->canBePlayed(mana, gold) ) cnt++;
    }
    return cnt;
}

