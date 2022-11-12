#include "CPlayerComputerExpert.h"


CPlayerComputerExpert::CPlayerComputerExpert(int hp, int mana, int gold, int attack) : CPlayerComputer(hp * 2, mana * 2,
                                                                                                       gold * 2,
                                                                                                       attack) {

}

string CPlayerComputerExpert::whatAmI() const {
    return "EXPERT";
}

void CPlayerComputerExpert::playing(CGame *pGame) {
    mana += 3; //gives player some mana

    int cnt = countPlayableCards();
    if (cnt == 1) {
        printw("Enemy drew a card");
        refresh();
        getch();
        pGame->drawCard(hand);
        return;
    }
    if (cnt == 0) {
        printw("Enemy went to a dungeon");
        refresh();
        getch();
        goToDungeon(nullptr,pGame);
        return;
    }

    int max = hand[0]->getEffect().cardValue;;
    int index = -1;

    shared_ptr<CPlayer> spFoo = enemyPlayer.lock();

    if (spFoo->getHP() < 20)
        for (unsigned int i = 0; i < hand.size(); i++) {
            if (hand[i]->canBePlayed(mana, gold))
                if (hand[i]->getEffect().hpEnemy > max) {
                    max = hand[i]->getEffect().hpEnemy;
                    index = i;
                }
        }
    if (index == -1)
        if (hp < 30)
            for (unsigned int i = 0; i < hand.size(); i++) {
                if (hand[i]->canBePlayed(mana, gold))
                    if (hand[i]->getEffect().cardValue > max) {
                        max = hand[i]->getEffect().cardValue;
                        index = i;
                }
        }
    if(index==-1)
        for(unsigned int i = 0 ; i < hand.size() ; i++){
            if( hand[i]->canBePlayed(mana, gold) )
                if (hand[i]->getEffect().hpSelf > max) {
                    max = hand[i]->getEffect().hpSelf;
                    index = i;
                }
        }
    if(index==-1) index = 0;

    string text="Enemy played " + hand[index]->getName() + " And it did:\n";
    if(hand[index]->getEffect().hpSelf != 0)
        text += "His life increased by " + to_string ( hand[index]->getEffect().hpSelf ) + "\n";
    if(hand[index]->getEffect().dmgSelf != 0)
        text += "His damage power increased by " + to_string ( hand[index]->getEffect().dmgSelf ) + "\n";
    if(hand[index]->getEffect().hpEnemy != 0)
        text += "Your life decreased by " + to_string ( hand[index]->getEffect().hpEnemy ) + "\n";
    if(hand[index]->getEffect().dmgEnemy != 0)
        text += "Your damage power decreased by " + to_string ( hand[index]->getEffect().dmgEnemy ) + "\n";

    printw(text.c_str());
    refresh();
    getch();

    playCard(index);
    hand.erase(hand.begin() + index);
}



