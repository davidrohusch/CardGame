#include "CPlayerHuman.h"
#include <curses.h>
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <string>
#include "Graphics.h"

CPlayerHuman::CPlayerHuman(int hp, int mana, int gold, int attack) : CPlayer(hp, mana, gold, attack) {
}

string CPlayerHuman::whatAmI() const {
    return "HUMAN";
}

void CPlayerHuman::goToDungeon(WINDOW *w, CGame *pGame) {
    srand(time(0));
    int goldgain = rand() % 10 + 1;
    int buffgain = rand() % 3 + 1;
    shared_ptr<CCard> randCard = pGame->randomCard();
    string dialog;



    int action = rand() % 3;
    switch(action){
        case(0):
            ///random card

            if(addCard( randCard)) {
                dialog = "You found this thingie underground : " + randCard->getName();
                printBox(w, dialog,25,0);

            }else{
                dialog = "You found this thingie underground : " + randCard->getName() + ". But your pockets are full.";
                printBox(w, dialog,25,0);

            }
            break;

        case(1):

            applyEffect(0,0,goldgain,0);
            dialog = "You found a troll. He dropped : " + to_string(goldgain) + " goldcoins on the ground.";
            printBox(w, dialog,25,0);
            ///random gold
            break;
        case(2):

            applyEffect(buffgain,buffgain,0,0);
            dialog = "You found a shrine. You feel stronger now." ;
            printBox(w, dialog,25,0);
            ///random buff
            break;
    }


}

void CPlayerHuman::playing(CGame *pGame) {
    bool turn = true;
    int ch;
    mana += 2; //give player some mana
    string dialog;
    int highlight=1;

    WINDOW *w = newwin(30, 100, 0, 0);

    mvwprintw(w, 1, 2, "hp:%d   attack:%d    gold:%d     mana:%d\n  F1) Draw card    F2) Go to dungeon  F3) attack enemy   F4) save game   F5) exit", hp, attack, gold, mana);
    drawCardMenu(w, highlight ,hand, gold, mana);
    keypad(stdscr, TRUE);



    shared_ptr<CPlayer> spFoo = enemyPlayer.lock();
    refresh();
    while(turn) {
        drawCardMenu(w, highlight ,hand, gold, mana);

        ch = getch();

        switch (ch) {
            case 10:
                try{
                    hand.at(highlight-1);
                }catch(std::out_of_range){
                    break;
                }
                if(hand[highlight-1]->canBePlayed(mana, gold)) {
                    playCard(highlight-1);
                    hand.erase(hand.begin() + highlight-1);
                    turn = false;
                }

                break;
            case KEY_UP:
                highlight--;
                if(highlight<1) highlight = hand.size();

                break;

            case KEY_DOWN:
                highlight++;
                if(highlight>hand.size()) highlight=1;

                break;

            case KEY_F(1):
                if (cardMax > hand.size()) {
                    try {
                        pGame->drawCard(hand);
                    }
                    catch (string &e) {
                        turn = false;
                        pGame->setStatus(false, false);
                        return;
                    }

                    printBox(w, "You drew a card. End of your turn!",25,0);
                    getch();
                    //clear();
                    turn = false;
                } else {
                    printBox(w, "You can not handle so manny cards",25,0);
                }

                break;
            case KEY_F(2):
                goToDungeon(w, pGame);
                turn = false;
                break;
            case KEY_F(3):
                attackPlayer(enemyPlayer.lock(), attack);

                printBox(w, "You attacked enemy with : " + to_string(attack) + " attack, now you need to rest for a round.",25,0);
                turn = false;
                break;
            case KEY_F(4):

                dialog = "SAVED SUCCESFULLY";
                try {
                    pGame->saveGame();
                }
                catch (...) {
                    dialog = "Evil witchers denied your will to save the game! (Saving failed)";
                }
                printBox(w, dialog,25,0);
                break;
            case KEY_F(5):
                pGame->setStatus(false, false);
                turn = false;
                break;

        }
    }

}


